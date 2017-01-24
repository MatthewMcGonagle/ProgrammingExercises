module Main where

import Text.Parsec
import Control.Monad

type RStringArray = [[String]]
type RCoordArray = [[Float]]
type Interval = (Float, Float)
type RIntervalArray = [Interval]

main :: IO ()
main = do
  let input = "0,0 2,2\n"
              ++ "1,1 3,3\n"
      parsedinput = parseRlines input 
      rectlist = do
                     result <- parsedinput
                     let coordlist = map convertRcoord result
                     return $ map convertRinterval coordlist 
      intersection = do
                         result <- rectlist
                         let initial = head result
                             rectlist = tail result 
                         return $ foldM intersectrect initial rectlist 
      intersectarea = do
                          result <- intersection
                          return $ area result
      prettyprint (Right x) = print x
      prettyoutput (Left x) = do
                                  putStrLn "There was an error"
                                  print x 
      prettyoutput (Right x) = do
                                  putStrLn "\nRectangles in the form of Cartesian Product of Intervals"
                                  prettyprint rectlist 
                                  putStrLn "\nThe intersection of the rectangles"
                                  prettyprint intersection
                                  putStrLn "\nThe area of the intersection"
                                  prettyprint intersectarea
  prettyoutput parsedinput 
                                
area :: Maybe RIntervalArray -> Float
area Nothing = 0
area (Just x) = foldl (\acc y -> acc * (length y)) 1 x 
     where length (a,b) = b - a

intersectrect :: RIntervalArray -> RIntervalArray -> Maybe RIntervalArray
intersectrect x y = let intervalpairs = zip x y
                        intersectpair z = intersectinterval (fst z) (snd z)
                    in
                    mapM intersectpair intervalpairs

intersectinterval :: Interval -> Interval -> Maybe Interval
intersectinterval x y = let a = maximum $ map fst [x,y]
                            b = minimum $ map snd [x,y]
                        in
                        case a > b of True -> Nothing
                                      False -> Just (a,b) 

convertRinterval :: RCoordArray -> RIntervalArray
convertRinterval [corner1, corner2] = zip corner1 corner2
convertRinterval x = [] 

convertRcoord :: RStringArray -> RCoordArray
convertRcoord x = map convertpair x
     where convertpair x = map read x 

rlines = endBy rect $ char '\n'

-- Example: rect parses "1,2 3,4.0" into 
-- Right [["1","2"], ["3","4.0"]] 
rect = sepBy coord $ char ' '
coord = sepBy numeral $ char ','
numeral = many $ oneOf "-.0123456789"

parseRlines :: String -> Either ParseError [RStringArray]
parseRlines input = parse rlines "(unkown)" input
