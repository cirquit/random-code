module Example1

open System

let square x = x * x

let list = [1..100]

let map    (f : 'a -> 'b)   (arg : 'a list) = List.map f arg
let filter (f : 'a -> bool) (arg : 'a list) = List.filter f arg


[<EntryPoint>]
let main _ =
    printfn "-----     OUTPUT     -----\n"
    printfn "This is the output %A" (map (fun x -> x * x) [1..10])
    printfn "\n-----   OUTPUT END   -----"
main()