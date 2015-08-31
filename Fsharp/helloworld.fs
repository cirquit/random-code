module ReadArgs

open System

[<EntryPoint>]
let main(args) =
    printfn "args: %A" args
    printfn "env.cmdline: %A" <| Environment.GetCommandLineArgs()
    0