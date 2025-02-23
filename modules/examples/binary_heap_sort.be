import binary_heap

var pi = [3,14,15,92,65,35,89,79,32,38,46,26,43,38,32,79,50,28,84,19,71,69,39]
# Display the elements of pi[] in ascending order
var h = pi.copy()
var less = / a b -> a < b, sort = binary_heap.sort
sort(h, less)
print(h)

# Display the 5 largest elements of pi[]
var cmp = / a b -> a > b
var max = []
binary_heap.make_heap(h, cmp)
for i: 1..5 max.push(binary_heap.remove_heap(h, cmp)) end
print(max)

# Display the 7 largest elements of pi[] in ascending order of index
h = []
for i: 0..pi.size()-1 h.push(i) end
cmp = / a b -> pi[a] > pi[b]
binary_heap.make_heap(h, cmp)
max = []
for i: 1..7 max.push(binary_heap.remove_heap(h, cmp)) end
sort(max, less)
for i: 0..6 print(f"{max[i]}: {pi[max[i]]}") end
