require './lib/list_item_simple'

experiment_data = []

k = 3

1.upto 9 do |children_count|

  leavers = []

  firstChild = ListItemSimple.new
  firstChild.val = 1

  latestChild = firstChild

  if children_count > 1
    lastChild = (2..children_count).inject(firstChild) do |prevChild, val|
      currentChild = ListItemSimple.new
      currentChild.val = val
      prevChild.next = currentChild
      currentChild.prev = prevChild
      currentChild
    end

    firstChild.prev = lastChild
    lastChild.next = firstChild

    (1..k).cycle do |remove_each|

      break if latestChild == latestChild.next

      if remove_each == k
        leavers << latestChild.val
        latestChild.prev.next, latestChild.next.prev = latestChild.next, latestChild.prev
      end

      latestChild = latestChild.next

    end

  end

  experiment_data << {
    children_count: children_count,
    leavers: leavers,
    winner: latestChild.val
  }

end

experiment_data.each do |result|
  puts "Children count: #{result[:children_count]}, Winner: #{result[:winner]}, Leavers: #{result[:leavers]}"
end