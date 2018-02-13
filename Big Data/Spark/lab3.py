from pyspark.sql import Row
from pyspark.sql import SparkSession

spark = SparkSession.builder.appName("SparkSQL").config("spark.some.config.option", "some-value").getOrCreate()

#Creating DataFrame from JSON file

sailors = spark.read.json("/user/ecc290/sailors.json")
reserves = spark.read.json("/user/ecc290/reserves.json")

sailors.show()
reserves.show()

sailors.printSchema()
sailors.select("sname").show()
sailors.select(sailors['sname'], sailors['age'] + 1).show()
sailors.filter(sailors['age'] > 21).show()
sailors.groupBy("age").count().show()

sailors.createOrReplaceTempView("sailors")
reserves.createOrReplaceTempView("reserves")
spark.sql("SELECT * FROM sailors").show()

# Creating DataFrame from RDD

sc = spark.sparkContext
lines = sc.textFile("/user/ecc290/boats.txt")
parts = lines.map(lambda l: l.split(","))
boatsRDD = parts.map(lambda p: Row(bid=int(p[0]), name=p[1], color=p[2]))

boats = spark.createDataFrame(boatsRDD)
boats.show()

boats.createOrReplaceTempView("boats")
spark.sql("SELECT * FROM boats").show()

# Write DataFrame to file

sailors.select("*").write.save("sailorscsv.csv", format="csv")

# Example

spark.sql("SELECT * FROM sailors WHERE rating > 7").show()

spark.sql("SELECT distinct(sid) FROM reserves R, boats B WHERE R.bid = B.bid AND color like '%red%'").show()

# Lab3

spark.sql("SELECT S.sname FROM sailors S WHERE S.sid NOT IN (SELECT R.sid FROM reserves R)").show();

spark.sql("SELECT S.sid FROM sailors S, boats B, reserves R WHERE S.sid = R.sid AND R.bid = B.bid AND B.color = 'red' AND S.sid NOT IN (SELECT S2.sid FROM sailors S2, boats B2, reserves R2 WHERE S2.sid = R2.sid AND R2.bid = B2.bid AND B2.color = 'green')").show()

spark.sql("SELECT S.sname FROM sailors S WHERE S.rating > (SELECT MAX(S1.rating) FROM sailors S1 WHERE S1.sname=\"horatio\")").show();
