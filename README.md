# ReducedSpaceSimulation
This is a C++ version of previous SimpleDeformation(a simple Matlab base code for testing new ideas).We provide a 
platform for experimenting new ideas on physical based simulation senarios. We mainly focus on elastic object in our 
current version. We want to explore the full potential of reduced space simulation in this project, and for the ultimate
 goal, we also hope that we can also provide a platform for simulating probelm involving contact.
### Main techniques
##### basis generation technique
* trajectory-bases basis generation using PCA analysis.
* modal analysis, which direcly compute or precompute the basis based on mass matrix and tangent stiffness matrix.
* skinning-based basis, which spread the deformation of a set of handles into their governing region based on some 
predefined distribution function like radial basis function.
##### reduced space simulation
* static cubature generation using greedy search, and hard limit threshhold filter.
* non-linear reduced space mapping using shallow neural network.
* dynamic cubature generation technique togather with multi grid approach(TODO)
##### some popular integrator
* BE,SI,SE,Newmark and alpha algorithm
* Euler-Rosenbrock exponential integrator (ERE)
* energy-preserving integrator including AVF and energy budgeting
#### contact simulation
* volume-based contact detection and simulation
* projective-dynamics approach and PBD

### Target and ultimate goal
* reduced the dimension of the problem and have an efficient and general reduced space dynamics
* try to dynamically compute the cubature and projection fast.
* by computing cubature and basis dynamically and locally, we may possibly be able to handly contact.
* introduce a framework that cover all these goal (we might need the power of MG).

### More
Now we have implemented some of the above algorhtim and test some ideas using matlab code. Now we are trying to 
implement a C++ version and increase the speed using GPU computing.
