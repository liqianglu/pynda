#ifndef LINALG_H
#define LINALG_H

#include <iostream>
#include "constants.h"

// * WARNING: I don't think the copy constructors do a deep copy. Never tested.
// * Could make more general by using templates, but... meh.

class sqm3d;

class vec3d;

class vec3d
{
    double x[d];
    public:
        vec3d ();
        vec3d (double, double, double);
        vec3d (double *);
        vec3d (const vec3d&);
        void set (double *);
        void set (double, double, double);
        void set (int, double);
        double norm ();
        double get (int);
        int getDim ();
        // Define the two notions of multiplication for vectors
        double dot (vec3d);
        vec3d cross (vec3d);
        // Operators and such 
        vec3d& operator= (const vec3d&);
        vec3d operator+ (vec3d);
        vec3d operator- (vec3d);
        double operator* (vec3d); // Inlcude the dot product as the default mult
        friend vec3d operator/ (const vec3d&, double);
        friend vec3d operator* (const vec3d&, double);
        friend vec3d operator* (double, const vec3d&);
        friend vec3d operator* (const sqm3d&, const vec3d&); // also in sqm3d
        friend vec3d operator* (const vec3d&, const sqm3d&); // also in sqm3d
        friend std::ostream& operator<< (std::ostream&, const vec3d&);
};

class sqm3d
{
    double m[d][d];
    public: 
        sqm3d ();
        sqm3d (double [][d]);
        sqm3d (const sqm3d&);
        void set (const double [][d]);
        void set (int, int, double);
        double det ();
        sqm3d transpose ();
        sqm3d inv ();
        // operators
        sqm3d& operator= (const sqm3d&);
        sqm3d operator+ (sqm3d);
        sqm3d operator- (sqm3d);
        sqm3d operator* (sqm3d);
        friend sqm3d operator* (double, const sqm3d&);
        friend sqm3d operator* (const sqm3d&, double);
        friend sqm3d operator/ (double, const sqm3d&);
        friend sqm3d operator/ (const sqm3d&, double);
        friend vec3d operator* (const sqm3d&, const vec3d&);
        friend vec3d operator* (const vec3d&, const sqm3d&);
        friend std::ostream& operator<< (std::ostream&, const sqm3d&);
};

#endif // LINALG_H