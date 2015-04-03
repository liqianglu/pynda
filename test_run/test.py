#!/usr/bin/env python2

import sys
sys.path.append ('../pywrap2/')
import panda
import random
import cv2
import numpy

box = panda.vec3d (1.0, 1.0, 1.0)
cell_size = panda.vec3d (0.2, 0.2, 0.2)
bi = panda.body_interactor (0.5, 0.5)
dt = 0.001
w = panda.world (box, cell_size, bi, dt)

x, v, r, m, I = panda.vec3d (), panda.vec3d (), 0.1, 0.1**2, 0.1**4/2

x[0], x[1] = 0.3, 0.5
v[0], v[1] = 1.0, 0
omega = panda.vec3d ()
omega[2] = 10*numpy.pi
s = panda.sphere (r, m, I, x, v, omega)
w.add_sphere (s)

s.x[0], s.v[0], s.w[2] = 0.7, -1, 0.0
w.add_sphere (s)

s.x[0], s.x[1], s.v[0], s.v[1], s.w[2] = 0.5, 0.2, 0.5, -1, 5*numpy.pi
w.add_sphere (s)


L = 512
for i in range (500):
    for j in range (5):
        w.step ()
    img = 255 - numpy.zeros ((L, L, 3), numpy.uint8)
    for j in range (w.num_spheres ()):
        s = w.get_sphere (j)
        xs, ys, rs, qs = int (s.x[0]*L), int (s.x[1]*L), int (s.r*L), s.q[2]
        color = (0, 0, 255) # BGR
        cv2.circle (img, (xs, ys), rs, color, -1, cv2.CV_AA)
        rs = rs-3
        cv2.circle (img, (xs, ys), rs, (0, 0, 0), 6, cv2.CV_AA)
        cv2.line (img, 
                  (xs, ys), 
                  (int (xs + rs*numpy.cos (qs)), int (ys + rs*numpy.sin (qs))),
                  (0, 0, 0), 6, cv2.CV_AA)
    cv2.imwrite ('images/' + str (i).zfill (5) + '.png', img)

