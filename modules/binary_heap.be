# https://en.wikipedia.org/wiki/Binary_heap
# similar to C++11 std::make_heap

def heapify(array, cmp, i)
  while true
    var m = i, child = 2 * i
    child += 1
    if child >= array.size() return end
    if cmp(array[child], array[m]) m = child end
    child += 1
    if child < array.size() && cmp(array[child], array[m]) m = child end
    if m == i break end
    var e = array[i]
    array[i] = array[m]
    i = m
    array[i] = e
  end
end

var binary_heap = module("binary_heap")

binary_heap.make_heap = def(array, cmp)
  var i = size(array) / 2
  while i >= 0 heapify(array, cmp, i) i -= 1 end
end

binary_heap.remove_heap = def(array, cmp)
  if array.size() == 0
    return array
  elif array.size() == 1
    return array.pop()
  end
  var m = array[0]
  array[0] = array.pop()
  heapify(array, cmp, 0)
  return m
end

# https://en.wikipedia.org/wiki/Heapsort
binary_heap.sort = def(array, cmp)
  var e = array.size(), root = e / 2
  while e > 1
    if root > 0
      root -= 1
    else
      e -= 1
      var top = array[0]
      array[0] = array[e]
      array[e] = top
    end

    var child = 2 * root + 1
    while child < e
      if child + 1 < e && cmp(array[child], array[child + 1]) child += 1 end
      var r = array[root]
      if !cmp(r, array[child]) break end
      array[root] = array[child]
      array[child] = r
      root = child
    end
  end
end

return binary_heap
