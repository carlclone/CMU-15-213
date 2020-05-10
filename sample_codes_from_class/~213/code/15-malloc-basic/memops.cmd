s
a 100
s
# Allocate increasingly larger blocks
a 200
a 400
a 600
a 800
a 100
# This one should fail
a 2000
# Overall allocation
s
# Free blocks with no coalescing (Case 1)
f 2
f 4
s
# Free blocks with coalescing (Cases 2 & 3)
f 1
f 5
s
# Free blocks with Case 4 coalescing
f 3
s
