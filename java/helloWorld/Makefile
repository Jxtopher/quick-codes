#
# @Author: Jxtopher
# @License: *
# @Date: 2018-10
# @Version: 1
# @Description: Makefile
#

.PHONY: all doc tests-unitaires run tests-unitaires

SOURCEDIR = sources
BUILDDIR = build


ifeq ($(OS),Windows_NT)
	SEPARATOR = ;
else
	SEPARATOR = :
endif

all: 
	javac -classpath "external-packages/*" -Xlint:unchecked -d $(BUILDDIR) $(SOURCEDIR)/mypackage/*
	cd $(BUILDDIR) ; jar cf app.jar mypackage/*
	javac -classpath "external-packages/*$(SEPARATOR)build/app.jar" -Xlint:unchecked -d build tests-unitaires/*
	cd $(BUILDDIR) ; jar cf appTest.jar mypackageTest/*

# doc:
# 	javadoc *

run:
	java -cp "build/app.jar" mypackage.Main


tests-unitaires:
	java -cp "external-packages/*$(SEPARATOR)build/app.jar$(SEPARATOR)build/appTest.jar" junit.textui.TestRunner  mypackageTest.test.junit.StackTest
	java -cp "external-packages/*$(SEPARATOR)build/app.jar$(SEPARATOR)build/appTest.jar" junit.textui.TestRunner  mypackageTest.test.junit.QueueTest