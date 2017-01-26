module Main where

import Text.Parsec
import Control.Monad
import System.IO

type RStringArray = [[String]]
newtype RCoord a = RCoord {getCoord :: [[a]]} 
newtype Interval a = Interval {getPair :: (a, a)}  
newtype RIntervals a = RIntervals {getIntervals :: [Interval a]} 

class Intersectable a where
     intersect :: a -> a -> Maybe a

     intersectall :: [a] -> Maybe a
     intersectall [] = Nothing
     intersectall (x:xs) = foldM intersect x xs  

main :: IO ()
main = do
  handle <- openFile "input.txt" ReadMode
  contents <- hGetContents handle
  let parsedinput = parseChallenges contents 
      challengelist = fmap ( map torectlist ) parsedinput
            where torectlist = map $ toRintervals . toRcorners
      intersection = fmap (map $ intersectall) challengelist
      intersectarea = fmap (map $ area) intersection
      prettyoutput (r, (i, ar)) =  do
                                        putStrLn "\nRectangles in the form of cartesian product of intervals:"
                                        print r 
                                        putStrLn "\nThe intersection of the rectangles as cartesian product:"
                                        print i 
                                        putStrLn "\nThe area of the intersection:"
                                        print ar 
      ziplist = (\a b c -> zip a $ zip b c) <$> challengelist <*> intersection <*> intersectarea
  case ziplist of (Left x) ->  do
                                    putStrLn "There was an error"
                                    print x 
                  (Right x) -> mapM_ prettyoutput x

instance (Show a) => Show (Interval a) where
     show (Interval (x,y)) = "(" ++ show x ++ "," ++ show y ++ ")"

instance (Show a) => Show (RCoord a) where
     show (RCoord x) = show x

instance (Show a) => Show (RIntervals a) where
     show (RIntervals x) = show x

prettyprint :: (Show a) => Either b a -> IO () 
prettyprint (Left x) = print ""
prettyprint (Right x) = print x

area :: (Num a) => Maybe (RIntervals a) -> a 
area Nothing = 0
area (Just x) = foldl (\acc y -> acc * (length y)) 1 $ getIntervals x 
     where length (Interval (a,b)) = b - a

instance (Ord a) => Intersectable (RIntervals a) where
      intersect x y = let intervalpairs = zip (getIntervals x) (getIntervals y)
                          intersectpair z = intersect (fst z) (snd z)
                      in
                      fmap RIntervals $ mapM intersectpair intervalpairs

instance (Ord a) => Intersectable (Interval a) where
     intersect x y = let z = maximum $ map (fst . getPair) [x,y]
                         w = minimum $ map (snd . getPair) [x,y]
                     in
                     case z > w of True -> Nothing
                                   False -> Just $ Interval (z,w) 

toRintervals :: (Ord a) => RCoord a -> RIntervals a
toRintervals (RCoord [corner1, corner2]) = RIntervals $ zipWith correctorder corner1 corner2
       where correctorder x y = Interval (minimum [x,y], maximum [x,y])
toRintervals x = RIntervals [] 

toRcorners :: RStringArray -> RCoord Float
toRcorners x = RCoord $ map convertpair x
     where convertpair x = map read x 

challenges = sepBy rlines $ blankline
blankline = char '\n'  
rlines = endBy rect $ char '\n'

-- Example: rect parses "1,2 3,4.0" into 
-- Right [["1","2"], ["3","4.0"]] 
dimension = 2
rect = do
            corner1 <- coord
            char ' '
            corner2 <- coord
            return [corner1, corner2]
coord = do
            firstcoord <- numeral 
            restcoords <- count (dimension-1) $ char ',' >> numeral 
            return $ firstcoord:restcoords
numeral = many $ oneOf "-.0123456789"

parseChallenges :: String -> Either ParseError [[RStringArray]]
parseChallenges input = parse challenges "(unkown)" input

parseRlines :: String -> Either ParseError [RStringArray]
parseRlines input = parse rlines "(unkown)" input
