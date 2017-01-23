module Main where

import Control.Monad.State

main :: IO ()
main = do
  -- The inputs to test. Parse them and then zip to get pretty output.
  let inputstringl = [ "1(234)56(789)"
                     , "1(2(34))56((789))"
                     , "1(2((3)(4)))56(789)"
                     , "(1(2((3)(4)))56(789))"
                     ]
      treel = map parse inputstringl 
      outstringl = map (\ (x,y) -> "String = " ++ x ++ "\n" ++ show y) (zip inputstringl treel)
  mapM_ putStrLn outstringl

-- Recursive data type that allows arrays of arrays
data ArrayTree a = Simply a | Node [ArrayTree a] 

-- show ArrayTree a prints out nested trees using ()
instance (Show a) => Show (ArrayTree a) where
    show (Simply x) = show x
    show (Node list) = showtree list
        where showtree = foldl concatshow [] 
                 where concatshow acc y = acc ++ (subshow y)
                        -- Display subtrees inside parenthesese
                        where subshow (Simply x) = show x
                              subshow (Node sublist) = " (" ++ (showtree sublist) ++ ") "

-- Function to parse the string into ArrayTree Char. Work really done by parseM.
parse :: String -> ArrayTree Char
parse x = let finalstate = runState (parseM x) [Node[]]
              trailing = fst $ finalstate
              [Node treel] = snd $ finalstate
          in
          Node $ treel ++ [trailing] 

-- Adds a tree x as a new node inside original tree, unless original tree is empty. When empty, just use x.
addoreatempty :: ArrayTree Char -> ArrayTree Char -> ArrayTree Char
addoreatempty (Node []) x = x
addoreatempty (Node treel) x = Node $ treel ++ [x]

-- Parses using state of array of ArrayTree which is of the form current:parent:grandparent:higherparents. Use foldM to accumulate current array of Char, then add into current ArrayTree Char state upon encountering '(' or ')'. 
parseM :: String -> State [ArrayTree Char] (ArrayTree Char)
parseM x = foldM addorbranch initial x
    where initial = Node []
          addorbranch :: (ArrayTree Char) -> Char -> State [ArrayTree Char] (ArrayTree Char) 
          -- Need to make new subtree. Add the accumulator into the current ArrayTree state. Then prepare 
          -- the subtree with a new current initial ArrayTree state. Also reset the accumulator to the initial state.
          addorbranch acc '(' = do
                                    (current:parents) <- get
                                    let (Node treel) = current 
                                        parent = Node $ treel ++ [acc] 
                                    put $ initial:parent:parents 
                                    return $ initial 
          -- Add accumulator to current ArrayTree state. Then add current state to parent state. 
          -- Start processing in parent state again.
          addorbranch acc ')' = do
                                    (current:parent:parents) <- get
                                    let (Node treel) = current 
                                        newtree = addoreatempty current acc 
                                        (Node ptreel) = parent
                                        current' = Node $ ptreel ++ [newtree] 
                                    put $ current':parents
                                    return $ initial 
          -- Simply update the accumulator when not encountering '(' or ')'.
          addorbranch (Node treel) x = return . Node $ treel ++ [Simply x] 

