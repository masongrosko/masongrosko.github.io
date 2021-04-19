#!/usr/bin/python
"""Final Project: Document Manipulation."""

# Import packages
import json
from bottle import route, run, request

from pymongo import MongoClient
from pymongo.collection import ReturnDocument

# Static Values
version = "v1.0"
database = "market"

# Pymongo
try:
    connection = MongoClient("localhost", 27017)
    db = connection[database]
except Exception as e:
    print(e)


# Create Stock
def _insert_document(request, collection, ticker):
    "Inserts document into the passed collection."
    collection = db[collection]
    document = request.json
    print(document)

    document["Ticker"] = ticker

    try:
        collection.insert_one(document)
    except Exception as ve:
        print(ve)
    return json.dumps(document, default=lambda x: str(x))


@route(
    "/<collection>/api/{version}/createStock/<ticker>".format(version=version),
    method="POST"
)
def insert_document(collection, ticker):
    """API Wrapper for insert document."""
    return _insert_document(request, collection, ticker)


# Get Stock
def _read_document(request, collection, ticker):
    "Returns contents of the document of the passed collection."
    collection = db[collection]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    query_params_dict["Ticker"] = ticker

    try:
        result = collection.find_one(query_params_dict)
        result = json.dumps(result, default=lambda x: str(x))
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/getStock/<ticker>".format(version=version),
    method="GET"
)
def read_document(collection, ticker):
    """API Wrapper for read document."""
    return _read_document(request, collection, ticker)


# Update Stock
def _update_document(request, collection, ticker):
    "Updates the contents of first found document of the passed collection."
    collection = db[collection]
    query_params_dict = request.json
    print(query_params_dict)
    updated_document = {
        x: y for x, y in query_params_dict.items()
        if x != "Ticker"
    }
    print(updated_document)
    print("")

    try:
        if not ticker:
            ticker = updated_document["Ticker"]
    except Exception as ve:
        result = ve


    try:
        result = collection.find_one_and_update(
            {"Ticker": ticker},
            {"$set": updated_document},
            return_document=ReturnDocument.AFTER
        )
        result = json.dumps(result, default=lambda x: str(x))
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/updateStock".format(version=version),
    method="PUT"
)
@route(
    "/<collection>/api/{version}/updateStock/<ticker>".format(version=version),
    method="PUT"
)
def update_document(collection, ticker=None):
    """API Wrapper for update document."""
    return _update_document(request, collection, ticker)


# Delete Stock
def _delete_document(request, collection, ticker):
    """Deletes the contents of first found document of the passed collection."""
    collection = db[collection]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.delete_one(query_params_dict).raw_result
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/deleteStock/<ticker>".format(version=version),
    method="GET"
)
@route(
    "/<collection>/api/{version}/deleteStock/<ticker>".format(version=version),
    method="DELETE"
)
def delete_document(collection, ticker):
    """API Wrapper for delete document."""
    return _delete_document(request, collection, ticker)


# Tests
@route(
    "/<collection>/api/{version}/testCreateStock/<ticker>".format(version=version),
    method="POST"
)
def _test_insert_document(collection, ticker):
    """Test insert document."""
    print("create", _insert_document(request, collection, ticker))
    print("read", _read_document(request, collection, ticker))
    print("delete", _delete_document(request, collection, ticker))


@route(
    "/<collection>/api/{version}/testDeleteStock/<ticker>".format(version=version),
    method="POST"
)
def _test_delete_document(collection, ticker):
    """Test delete document."""
    print("create", _insert_document(request, collection, ticker))
    print("read", _read_document(request, collection, ticker))
    print("delete", _delete_document(request, collection, ticker))
    print("read", _read_document(request, collection, ticker))


# Simple Moving Average
def _find_SMA(request, collection):
    """Find stocks with 50-day Simple Moving Average within passed range"""
    collection = db[collection]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.find(
            {
                "50-Day Simple Moving Average": {
                  "$gt": float(query_params_dict["low"]),
                  "$lt": float(query_params_dict["high"])
                }
            }
        ).count()
        result = str(result)
    except Exception as ve:
        print(ve)
        result = ve
    return result


@route(
    "/<collection>/api/{version}/findSMA".format(version=version),
    method="GET"
)
def find_SMA(collection):
    """API Wrapper for 50-day SMA."""
    return _find_SMA(request, collection)


# Industry String Search
def _industry_string_search(request, collection, industry):
    """Find stocks with industries matching passed request."""
    collection = db[collection]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.find(
            {
                "Industry": query_params_dict.get("Industry", industry)
            },
            {"_id": 0, "Ticker": 1}
        )
        result = [x for x in result]
        result = json.dumps(result, default=lambda x: str(x))
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/findIndustry".format(version=version),
    method="GET"
)
@route(
    "/<collection>/api/{version}/findIndustry/<industry>".format(version=version),
    method="GET"
)
def industry_string_search(collection, industry=None):
    """API Wrapper for Industry Search."""
    return _industry_string_search(request, collection, industry)


# Aggregation Pipeline
def _aggregation_pipeline(request, collection, sector):
    """Transforms documents into aggregated results using multiple pipeline stages."""
    collection = db[collection]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.aggregate(
            [
                {
                    "$match": {"Sector": query_params_dict.get("Sector", sector)}
                }, {
                    "$group": {
                        "_id": "$Industry",
                        "Total Shares Outstanding": {
                          "$sum": "$Shares Outstanding"
                        }
                    }
                }
            ]
        )
        result = [x for x in result]
        result = json.dumps(result, default=lambda x: str(x))
    except Exception as ve:
        result = ve
    return result

@route(
    "/<collection>/api/{version}/aggregateSector".format(version=version),
    method="GET"
)
@route(
    "/<collection>/api/{version}/aggregateSector/<sector>".format(version=version),
    method="GET"
)
def aggregation_pipeline(collection, sector=None):
    """API Wrapper for aggregation pipeline."""
    return _aggregation_pipeline(request, collection, sector)


# Restful API
def _stock_report(request, collection, tickers=None):
    """Create a summarized stock report for all passed tickers."""
    collection = db[collection]
    if not tickers:
      tickers = request.json

    try:
        result = collection.find(
            {"$text": {"$search": " ".join(tickers)}},
            {
                "_id": 0,
                "Ticker": 1,
                "Company": 1,
                "Industry": 1,
                "Price": 1,
                "P/E": 1,
                "PEG": 1,
                "EPS growth past 5 years": 1,
                "Dividend Yield": 1
            }
        )
        result = [x for x in result]
        result = json.dumps(result, default=lambda x: str(x))
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/stockReport".format(version=version),
    method="GET"
)
def stock_report(collection):
    """API Wrapper for stock report."""
    return _stock_report(request, collection)


def _industry_report(request, collection_name, industry):
    """Report top five stocks based on passed industry."""
    collection = db[collection_name]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.find(
            {"$text": {"$search": '"' + query_params_dict.get("Industry", industry) + '"'}},
            {"Ticker": 1, "EPS growth past 5 years": 1}
        ).sort([("EPS growth past 5 years", -1)]).limit(5)
        tickers = [x["Ticker"] for x in result]
        print(tickers)
        result = _stock_report(request=request, collection=collection_name, tickers=tickers)
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/industryReport/<industry>".format(version=version),
    method="GET"
)
def industry_report(collection, industry):
    """API Wrapper for industry_report."""
    return _industry_report(request, collection, industry)


def _company_report(request, collection_name, company):
    """Company stock report."""
    collection = db[collection_name]
    query_params_dict = dict(request.query)
    print(query_params_dict)

    try:
        result = collection.find(
            {"$text": {"$search": '"' + query_params_dict.get("Industry", company) + '"'}},
            {"Ticker": 1}
        )
        tickers = [x["Ticker"] for x in result]
        print(tickers)
        result = _stock_report(request=request, collection=collection_name, tickers=tickers)
    except Exception as ve:
        result = ve
    return result


@route(
    "/<collection>/api/{version}/companyReport/<company>".format(version=version),
    method="GET"
)
def company_report(collection, company):
    """API Wrapper for company_report."""
    return _company_report(request, collection, company)



# Simple main applications
class test_request:
    pass


def main_update_document():
    """Simple main application to call update document."""
    fake_request = test_request()
    fake_request.json = {"Ticker": "TEST", "Volume": 1000}

    return _update_document(
        request=fake_request,
        collection="stocks",
        ticker=None
    )


def main_find_SMA():
    """Simple main application to call find SMA."""
    fake_request = test_request()
    fake_request.query = {"high": "1.5", "low": "1"}

    results = _find_SMA(request=fake_request, collection="stocks")
    print(results)
    return results


def main_industry_string_search():
    """Simple main application to call industry_string_search."""
    fake_request = test_request()
    fake_request.query = {}

    results = _industry_string_search(
        request=fake_request,
        collection="stocks",
        industry="Medical Laboratories & Research"
    )
    print(results)
    return results


def main_aggregation_pipeline():
    """Simple main application to call aggregation_pipeline."""
    fake_request = test_request()
    fake_request.query = {}

    results = _aggregation_pipeline(
        request=fake_request,
        collection="stocks",
        sector="Healthcare"
    )
    print(results)
    return results


if __name__ == '__main__':
    #app.run(debug=True)
    run(host='localhost', port=8080)
    main_update_document()
    main_find_SMA()
    main_industry_string_search()
    main_aggregation_pipeline()
