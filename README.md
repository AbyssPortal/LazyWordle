# A simple implementation of a wordle solver.
## This solver works in the following way:
  First, initialize partition to be all the allowed wordle results
  then, we find a good guess for the partition.
  then, we use this good guess. It gives us some data, in the form of green, yellow and black squares. these invalidate most of the words in our partition.
  Now, we set the partition to be only the words which are valid after this new guess
  repeat until the partition is only 1 element
  
  ### We find good guesses in the following way:
  iterate over all legal wordle words. for all of those, iterate over all the possible results from the partition. now, each of those will assign a different coloring to our word. 
  our word's score is 2 * the maximum amount of results that give the same coloring. remove one from the score if the word is also a legal result
  take the word with the minimum score

  This is essentially an extension of binary space, just without the nice properties of numbers. we choose the reuslt which narrows down our space the most in the worst case - which is also a description of what binary search does.

  This solver can solve all the words in the input data in 6 or less guesses, with an average of 3.74 guesses. 
  the [optimal algorithm](https://sonorouschocolate.com/notes/index.php?title=The_best_strategies_for_Wordle)  can solve everything in 5 or less guesses, with an average of 3.42 guesses. 
  The difference is, this algorithm runs nearly instantly, except for the first guess which can be cached, which takes \~1 second, whereas the optimal algorithm takes 1~2 days to compute (which can be cached and turned into a strategy file)
  
