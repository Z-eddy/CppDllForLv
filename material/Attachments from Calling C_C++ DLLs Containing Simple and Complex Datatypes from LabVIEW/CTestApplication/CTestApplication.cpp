//==============================================================================
//
// Title:       CVITestApplication
// Purpose:     A short description of the command-line tool.
//
// Created on:  11/3/2009 at 10:20:31 AM by J J.
// Copyright:   NI. All Rights Reserved.
//
//==============================================================================

//==============================================================================
// Include files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PassingDataSampleDLL.h"

#pragma warning(disable : 4996)

//==============================================================================
// Constants

//==============================================================================
// Types

//==============================================================================
// Static global variables

//==============================================================================
// Static functions


//==============================================================================
// Global variables

//==============================================================================
// Global functions
int main (int argc, char *argv[])
{	
	PrintFunctionDescription("ReturningAValue_Integer", "This function returns -1");
	{
		int num = ReturningAValue_Integer();		
		printf("\nReturn Value: %d", num);
	}

	PrintFunctionDescription("ReturningAValue_PointerToInteger", "This function returns an integer pointer with value -1");
	{		
		int* num = ReturningAValue_PointerToInteger();
		printf("\nReturn Value: %d", *num);
	}

	PrintFunctionDescription("PassingParameters_Integer", "This function returns the sum of two numbers");
	{
		int x = 5;
		int y = 3;
		int sum = 0;
		sum = PassingParameters_Integer(x, y);
		printf("\nx: %d, y: %d, sum: %d", x, y, sum);
	}

	PrintFunctionDescription("ReturningValuesByReference_Integer", "This function returns the sum of two numbers by reference");
	{
		int x = 5;
		int y = 3;
		int sum = 0;
		ReturningValuesByReference_Integer(x, y, &sum);
		printf("\nx: %d, y: %d, sum: %d", x, y, sum);
	}
	
	PrintFunctionDescription("PassingParamters_ArrayOfIntegers", "This function returns the sum of the numbers in an integer array");
	{
		int x[3] = {1,2,3};
		int length = 3;
		int sum = PassingParamters_ArrayOfIntegers(x, length);
		printf("\nx: {%d,%d,%d}, length: %d, sum: %d", x[0], x[1], x[2], length, sum);
	}
	
	PrintFunctionDescription("ReturningAValue_ArrayOfIntegers", "This function returns an array of integers of length specified by the length paramter. Values are 0...length-1.");
	{
		int length = 3;
		int *x;
		x = ReturningAValue_ArrayOfIntegers(length);								  
		printf("\nlength: %d, x: {%d,%d,%d}", length, x[0], x[1], x[2]);
	}
	
	PrintFunctionDescription("ReturningValuesByReference_ArrayOfIntegers", "This function takes an array and returns ny reference a duplicate new array with an extra integer (-1) at the end");
	{
		int x[3] = {1,2,3};
		int length = 3;
		int newLength;
		int *newArray = NULL;
		ReturningValuesByReference_ArrayOfIntegers(x, length, &newArray, &newLength);
		printf("\nx: {%d,%d,%d}, length: %d, newArray: {%d,%d,%d,%d}, newLength: %d", x[0], x[1], x[2], length, newArray[0], newArray[1], newArray[2], newArray[3], newLength);
	}

	PrintFunctionDescription("ReturningAValue_String", "This function returns the string \"Hello World\"");
	{
		char *str = ReturningAValue_String();
		printf("\nstr: %s", str);
	}

	PrintFunctionDescription("PassingParamters_String", "This function takes a string and returns its length");
	{
		char *str = "Hello World";
		int length = PassingParamters_String(str);
		printf("\nstr: %s, length: %d", str, length);
	}

	PrintFunctionDescription("ReturningValuesByReference_String", "This function takes a string and returns by reference a duplicate string with \"++\" appended");
	{
		char *str = "Hello World";
		char *newString = NULL;
		ReturningValuesByReference_String(str, &newString);
		printf("\nstr: %s, newString: %s", str, newString);
	}

	PrintFunctionDescription("ReturningAValue_2DArrayOfIntegers", "This function returns a 2D array of integers with element values equal to row+col");
	{
		int **x = ReturningAValue_2DArrayOfIntegers(2, 2);
		printf("\nx: {{%d, %d}, {%d, %d}}", x[0][0], x[0][1], x[1][0], x[1][1]);
	}

	PrintFunctionDescription("PassingParamters_2DArrayOfIntegers", "This function takes a 2D array of integers and returns the sum of its elements");
	{
		int x[2][2] = {{1,2},{3,4}};
		int sum = PassingParamters_2DArrayOfIntegers((int *)x, 2, 2);
		printf("\nx: {{%d, %d}, {%d, %d}}, sum: %d", x[0][0], x[0][1], x[1][0], x[1][1], sum);
	}

	PrintFunctionDescription("ReturningValuesByReference_2DArrayOfIntegers", "This function returns by reference a 2D array of integers with element values equal to row+col");
	{
		int **x = NULL;
		ReturningValuesByReference_2DArrayOfIntegers(2, 2, &x);
		printf("\nx: {{%d, %d}, {%d, %d}}", x[0][0], x[0][1], x[1][0], x[1][1]);
	}

	PrintFunctionDescription("ReturningAValue_SimpleStruct", "This function returns a simple structure (circle)");
	{
		struct simpleStructCircle circle = ReturningAValue_SimpleStruct();
		printf("\ncircle.x: %f, circle.y: %f, circle.radius: %f", circle.x, circle.y, circle.radius);
	}

	PrintFunctionDescription("ReturningAValue_PointerToSimpleStruct", "This function returns a pointer to a simple structure (circle)");
	{
		struct simpleStructCircle *circle = ReturningAValue_PointerToSimpleStruct();
		printf("\ncircle.x: %f, circle.y: %f, circle.radius: %f", (*circle).x, (*circle).y, (*circle).radius);
	}

	PrintFunctionDescription("PassingParamters_SimpleStruct", "This function takes a simple structure (circle) and returns its area");
	{
		struct simpleStructCircle circle = {1, 1, 3};
		float area = PassingParamters_SimpleStruct (circle);
		printf("\ncircle.x: %f, circle.y: %f, circle.radius: %f, area: %f", circle.x, circle.y, circle.radius, area);
	}

	PrintFunctionDescription("ReturningValuesByReference_SimpleStruct", "This function takes a simple structure (circle) and returns a duplicate simple struct (circle) by reference with double the radius");
	{
		struct simpleStructCircle circle = {1, 1, 3};
		struct simpleStructCircle largerCircle;
		ReturningValuesByReference_SimpleStruct (circle, &largerCircle);
		printf("\ncircle.x: %f, circle.y: %f, circle.radius: %f, largerCircle.x: %f, largerCircle.y: %f, largerCircle.radius: %f, ", circle.x, circle.y, circle.radius, largerCircle.x, largerCircle.y, largerCircle.radius);
	}

	PrintFunctionDescription("ReturningValuesByReference_ArrayOfSimpleStruct", "This function returns by reference an array of simple struct (circle), where each circle has x, y and radius = i");
	{
		int length = 2;
		int i;
		struct simpleStructCircle *circleArray = NULL;
		ReturningValuesByReference_ArrayOfSimpleStruct(&circleArray, length);
		for (i=0; i<length; i++)
			printf ("\ncircle[%d].x: %f, circle[%d].y: %f, circle[%d].radius: %f", i, circleArray[i].x, i, circleArray[i].y, i, circleArray[i].radius);
	}

	PrintFunctionDescription("ReturningAValue_ComplexStruct", "This function returns a complex structure (polygon)");
	{
		int i;
		struct complexStructPolygon triangle = ReturningAValue_ComplexStruct();
		printf("\ntriangle.name: %s, Vertices: ", triangle.name);
		for (i=0; i<triangle.numVertices; i++)
			printf("{%d, %d}, ", triangle.vertices[i].x, triangle.vertices[i].y);
	}

	PrintFunctionDescription("ReturningAValue_PointerToComplexStruct", "This function returns a pointer to a complex structure (polygon)");
	{
		int i;
		struct complexStructPolygon *triangle = ReturningAValue_PointerToComplexStruct();
		printf("\ntriangle.name: %s, Vertices: ", (*triangle).name);
		for (i=0; i<(*triangle).numVertices; i++)
			printf("{%d, %d}, ", (*triangle).vertices[i].x, (*triangle).vertices[i].y);
	}

	PrintFunctionDescription("PassingParamters_ComplexStruct", "This function takes a complex struct (polygon) and returns the maximum y value");
	{
		struct complexStructPolygon triangle = ReturningAValue_ComplexStruct();
		int max = PassingParamters_ComplexStruct(triangle);
		int i;
		printf("\ntriangle.name: %s, Vertices: ", triangle.name);
		for (i=0; i<triangle.numVertices; i++)
			printf("{%d, %d}, ", triangle.vertices[i].x, triangle.vertices[i].y);
		printf("MaxY: %d", max);
	}

	PrintFunctionDescription("ReturningValuesByReference_PointerToComplexStruct", "This function returns a complex structure (polygon) by reference");
	{
		int i;
		struct complexStructPolygon triangle;
		ReturningValuesByReference_PointerToComplexStruct(&triangle);
		printf("\ntriangle.name: %s, Vertices: ", triangle.name);
		for (i=0; i<triangle.numVertices; i++)
			printf("{%d, %d}, ", triangle.vertices[i].x, triangle.vertices[i].y);
	}

	PrintFunctionDescription("ReturningValuesByReference_ArrayOfComplexStruct", "This function returns by reference an array of complex struct (polygon)");
	{
		int length = 2;
		int i, y;
		struct complexStructPolygon *triangles = NULL;
		ReturningValuesByReference_ArrayOfComplexStruct(&triangles, length);
		for (i=0; i<length; i++)
		{
			printf("\ntriangles[i].name: %s, Vertices: ", triangles[i].name);
			for (y=0; y<triangles[i].numVertices; y++)
				printf("{%d, %d}, ", triangles[i].vertices[y].x, triangles[i].vertices[y].y);
		}
	}

    printf("\n\nPress Enter to Exit...");
	getchar();
    return 0;
}



