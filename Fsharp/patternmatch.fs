module PatternMatching

open System

let map     (f : 'a -> 'b)   (xs : 'a list) = List.map f xs
let mapM_   (f : 'a -> unit) (xs : 'a list) = List.iter f xs
let filter  (f : 'a -> bool) (xs : 'a list) = List.filter f xs
let foldl   (f : 'a -> 'b -> 'a) (start : 'a) (xs : 'b list) = List.fold f start xs
let foldr   (f : 'a -> 'b -> 'b) (start : 'b) (xs : 'a list) = List.foldBack f xs start
let zipWith (f : 'a -> 'b -> 'c) (xs : 'a list) (ys : 'b list) = List.map2 f xs ys
let scanl   (f : 'a -> 'b -> 'a) (start : 'a) (xs : 'b list) = List.scan f start xs
let scanr   (f : 'a -> 'b -> 'b) (start : 'b) (xs : 'a list) = List.scanBack f xs start
let sort    (xs : 'a list) = List.sort xs


// drop the first and last element from a list
let f (xs : 'a list) =
    let rec g (xs : 'a list) (acc : 'a list) =
        match xs, acc with
        | []     , _   -> acc
        | [h]    , acc -> acc
        | h::n::t, []  -> g t [n]
        | h::t   , acc -> g t (acc @ [h])
    g xs []

// primes until bound
let primes (bound : int) =
    let rec sieve (xs : int list) =
        match xs with
        | []   -> List.empty
        | h::t -> h::sieve [for x in t do if not (x % h = 0) then yield x]
    sieve [2..bound]

  // Maybe type
let someVal = Some (1)
let noVal   = None

let patternMatch input =
    match input with
    | Some _ -> printf "Some value"
    | _      -> printf "Something else"

// Tuples

let twoTup = 1,2
let threeTup = "Hello",2,1.0

// custom Types

type Temp =
    | F of float
    | C of float

let inC = C 32.7


printf "\n\n-----   OUTPUT   -----\n\n"
//printf "%A" (primes 1000)
printf "\n\n-----   OUTPUT END   -----\n\n"

//mapM_ (fun x -> printfn "%d" x) (f [1;2;3;4])

//[<EntryPoint>]
//let main(args) =
//    printfn "args: %A" (f args)
//    0