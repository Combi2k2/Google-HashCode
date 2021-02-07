Solution is based on following explanation:

https://a3nm.net/blog/google_hashcode_2014.html

Header file CrucialData.hpp holds the neccessary variables (declared in the problem statement)

Header file Greedy.hpp naively solve the problem with greedy algorithm:
* Find the "most" optimal direction from current point (actually only most optimal in next 10 steps) with assist of backtrack implementation
* Follow that direction
* Back to step 1 until the points gained from that direction is zero
