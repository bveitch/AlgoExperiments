# AlgoExperiments
Experiments with faster ways of computing trivial things

Eg:
1. n!= factorial(n)=n*factorial(n-1)

This defines almost the most basic recursion. But is there a faster way?
Legendre reliazed that n! can also be expressed,

n!= Product_{p in primes} p^a_p

where,

a_p=Sum_{i=1}^{\infinity} floor(n/p^i)

This ought to be O(n/log(n)) in time and memory. In memory as must first build a prime list via sieving.

2. Fibonacci numbers.

I hear (and have heard) this often comes upin coding interviews. It can be defined iteratively, 

F[1]=1, F[2]=1,

F[n+1]=F[n] + F[n-1]

This is O(n) in time using a procedural loop. There are faster ways. the supriose hear was that C++ in built pow function doesnt seem optimum, 
so O(log_2 n) running times were missed. A fast powering trick was included for this purpose.
