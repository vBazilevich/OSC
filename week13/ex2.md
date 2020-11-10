# Exercise 2: Strategies to deal with deadlocks

## Recovery
Deals with problem only when it actually occurs. Can kill some processes who are
in a deadlock state. However, it requires to have processes which can be restarted
without any ill effects and which do not require some specific state of resources
they were holding.

## Prevention
As it checks for the potential deadlock on each request and it is time consuming,
this strategy obviously can not be used in a real-time systems. However, in a
non time critical systems it can be used.

## Avoidance
Makes deadlocks impossible, but it puts extra constraints on programs which
will be runned on this system, what makes them more complicated in terms
of development.
