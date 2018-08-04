#!/usr/bin/env python
#-*- coding: utf-8 -*-
# Python 3.7

#
# @Author: Jxtopher
# @License: *
# @Date: 2018-08-04
# @Version: V1
# @Purpose: Exemple d'utitlisation de mongodb
#

import pymongo

data = [[2018, 7, 157],  [2018, 6, 213],  [2018, 5, 223],  [2018, 4, 164],
 [2018, 3, 103],  [2018, 2, 313],  [2018, 1, 200],  [2017, 12, 148],
 [2017, 11, 228], [2017, 10, 261], [2017, 9, -33],  [2017, 8, 156],
 [2017, 7, 209],  [2017, 6, 222],  [2017, 5, 138],  [2017, 4, 211],
 [2017, 3, 98],  [2017, 2, 235],  [2017, 1, 227],  [2016, 12, 156],
 [2016, 11, 178],  [2016, 10, 161],  [2016, 9, 156],  [2016, 8, 151],
 [2016, 7, 255],  [2016, 6, 287],  [2016, 5, 38],  [2016, 4, 160],
 [2016, 3, 215],  [2016, 2, 242],  [2016, 1, 151],  [2015, 12, 292],
 [2015, 11, 211],  [2015, 10, 271],  [2015, 9, 142],  [2015, 8, 173],
 [2015, 7, 215],  [2015, 6, 223],  [2015, 5, 280],  [2015, 4, 223],
 [2015, 3, 126],  [2015, 2, 295],  [2015, 1, 257],  [2014, 12, 252],
 [2014, 11, 321],  [2014, 10, 214],  [2014, 9, 248],  [2014, 8, 142],
 [2014, 7, 209],  [2014, 6, 288],  [2014, 5, 217],  [2014, 4, 288],
 [2014, 3, 192],  [2014, 2, 175],  [2014, 1, 113],  [2013, 12, 74],
 [2013, 11, 203],  [2013, 10, 204],  [2013, 9, 148],  [2013, 8, 169],
 [2013, 7, 162],  [2013, 6, 195],  [2013, 5, 175],  [2013, 4, 165],
 [2013, 3, 88],  [2013, 2, 236],  [2013, 1, 157]]

def insert(_data, collection):
    listOfdict = []
    for i in range(0, len(_data)):
        listOfdict.append({"année":_data[i][0], "mois":_data[i][1], "capteur":_data[i][2]})
    collection.insert_many(listOfdict)

def show(collection):
    for i in collection.find({}):
        print(i)

def query_group(collection):
    print("[+] Les valeurs du capteur agrégé pour l'ensemble de la collection :")
    _query = [{"$group":
              {"_id": "null",
              "averageValue" :{"$avg": "$capteur"},
              "maxValue" :{"$max": "$capteur"},
              "minValue" :{"$min": "$capteur"},
              }
             }]
    results = collection.aggregate(_query)
    print(list(results))

    print("[+] Les valeurs du capteur agrégé en fonction des années :")
    _query = [{"$group":
              {"_id": "$année",
              "averageValue" :{"$avg": "$capteur"},
              "maxValue" :{"$max": "$capteur"},
              "minValue" :{"$min": "$capteur"},
              }
             }]
    results = collection.aggregate(_query)
    print(list(results))

def query_serach(collection):
    _query = {"année": 2018, "mois": 4}
    x = collection.find(_query )
    for i in x:
        print(i)

if __name__ == '__main__':
    client = pymongo.MongoClient()
    db = client["example"]
    collection = db["mers"]

    insert(data, collection)
    show(collection)
    query_group(collection)
    query_serach(collection)
