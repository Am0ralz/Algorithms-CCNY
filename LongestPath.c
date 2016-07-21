//Angel Morales

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//structure for an intersection point of two lines
struct point {
    double x; //the x coordinate of the point
    double y; //the y coordinate of the point
    int line1; //the first intersecting line on which the point lies
    int line2; //the second intersecting line on which the point lies
    double length; //the length of the longest x-monotone path that ends in this point
};

//sorts the array of n points in ascending order based on their x coordinate
void sortPoints(struct point *points, int n)
{
    int i, j;

    //for all positions in the array except the last
    for (i = 0; i < n - 1; i++)
    {
        //find the smallest x value in the rest of the array
        int small = i;
        for (j = i + 1; j < n; j++)
        {
            if (points[j].x < points[small].x)
            {
                small = j;
            }
        }

        //swap the values of the current element and the smallest element that was found
        struct point aux = points[i];
        points[i] = points[small];
        points[small] = aux;
    }
}

//returns the distance between the two points
double dist(struct point point1, struct point point2)
{
    //the formula for the distance of two points in 2D
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
};

//prints the longest x-monotone path 
//n: number of lines
//a, b, c: arrays of the a, b, c coefficients for the lines
void longest_path(int n, int *a, int *b, int *c)
{
    int numIntersect = 0; //number of intersections of the lines

    int i, j;

    //count the number of intersections based on the number of lines
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            numIntersect++;
        }
    }

    //allocate an array for the intersection points
    struct point *intersect = (struct point*)malloc(numIntersect * sizeof(struct point));

    //start counting the intersections again as we compute them
    numIntersect = 0;

    //compute all the intersections and store them in the array
    for (i = 0; i < n; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            intersect[numIntersect].line1 = i; //line 1
            intersect[numIntersect].line2 = j; //line 2
            //compute the intersection point
            intersect[numIntersect].x = ((b[j] * c[i]) - (b[i] * c[j])) / (double)((a[i] * b[j]) - (a[j] * b[i]));
            intersect[numIntersect].y = ((a[i] * c[j]) - (a[j] * c[i])) / (double)((a[i] * b[j]) - (a[j] * b[i]));
            intersect[numIntersect].length = 0;

            numIntersect++;
        }
    }

    //sort the intersections into an ascending order based on the x coordinate
    sortPoints(intersect, numIntersect);

    //for all the intersection points
    //compute the length of the longest x-monotone path that ends in this point
    for (i = 0; i < numIntersect; i++)
    {
        //go backward and check the previous points (if any of them lies on the first line of the current intersection)
        for (j = i - 1; j >= 0; j--)
        {
            //if there is a previous point on the first line of the current intersection
            if (intersect[i].line1 == intersect[j].line1 || intersect[i].line1 == intersect[j].line2)
            {
                //compute the length for the current point as the sum of the previous point's length and the distance from the previous point to the current one
                double length = intersect[j].length + dist(intersect[j], intersect[i]);

                //if the computed length is greater than the current length of the current point, update it
                if (length > intersect[i].length)
                {
                    intersect[i].length = length;
                }

                //we have already found a previous point on the first line of the current intersection, no need to check any further
                break;
            }
        }

        //go backward and check the previous points (if any of them lies on the second line of the current intersection)
        for (j = i - 1; j >= 0; j--)
        {
            //if there is a previous point on the second line of the current intersection
            if (intersect[i].line2 == intersect[j].line1 || intersect[i].line2 == intersect[j].line2)
            {
                //compute the length for the current point as the sum of the previous point's length and the distance from the previous point to the current one
                double length = intersect[j].length + dist(intersect[j], intersect[i]);

                //if the computed length is greater than the current length of the current point, update it
                if (length > intersect[i].length)
                {
                    intersect[i].length = length;
                }

                //we have already found a previous point on the first line of the current intersection, no need to check any further
                break;
            }
        }
    }

    //find the point with largest length value
    int largest = 0; //by default it is the first point
    //check all the other points
    for (i = 1; i < numIntersect; i++)
    {
        //if the length of the current point is larger than the largest, make it the largest
        if (intersect[i].length > intersect[largest].length)
        {
            largest = i;
        }
    }

    //we go backward from the point with largest length to reconstruct the path
    struct point current = intersect[largest];

    //allocate array for the lines of the path
    int *lines = (int*)malloc(numIntersect * sizeof(int));
    int index = 0; //index into the array of lines where we will save the next line
    int lastLine = -1; //the last line that we have found, by default -1 indicating that we have not yet found any lines

    //go from the intersection with largest length value backwards
    for (i = largest - 1; i >= 0; i--)
    {
        //if the length of the previous intersection + the distance to the current intersection is equal to the length of the current intersection
        //it means the line between the two intersections is part of the path
        if (fabs(intersect[i].length + dist(intersect[i], current) - current.length) < 0.0001)
        {
            //we check which of the two lines of the current intersection is shared with the previous intersection and save it
            if ((current.line1 == intersect[i].line1 || current.line1 == intersect[i].line2) && current.line1 != lastLine)
            {
                lastLine = current.line1;
                lines[index] = lastLine;
                index++;
            }
            else if ((current.line2 == intersect[i].line1 || current.line2 == intersect[i].line2) && current.line2 != lastLine)
            {
                lastLine = current.line2;
                lines[index] = lastLine;
                index++;
            }

            //make the previous intersection the current intersection
            current = intersect[i];

            //we reached the beginning of the path
            if (current.length == 0) break;
        }
    }

    //print the lines of the path in reversed order because they were put into the array in the order from last to first
    printf("sequence of lines taken by the longest path: ");
    for (index = index - 1; index >= 0; index--)
    {
        printf("%d ", lines[index]);
    }
    printf("\n");

    //the total length is the length in the last intersection of the path
    printf("total length: %f\n", intersect[largest].length);

    //deallocate the arrays
    free(lines);
    free(intersect);
}

int main(void) {
    int a[20], b[20], c[20];
    int i;
    for (i = 0; i < 20; i++) {
        a[i] = (20 - i);
        b[i] = -1 * (i + 1);
        c[i] = a[i] * b[i];
    }
    printf("calling longest_path()\n");
    longest_path(20, &(a[0]), &(b[0]), &(c[0]));
    printf(" longest path should start intersection line 18 and 19, then continue\n");
    printf("along line 19 to its intersection with line 0, end at intersection line 0 and line 1.\n");
    printf("End Test\n");
    return 0;
}