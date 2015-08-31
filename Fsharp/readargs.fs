open System

[<EntryPoint>]
let main(args) =
    printfn "args: %A" args
    printfn "env.cmdline: %A" <| Environment.GetCommandLineArgs()
    0

//Run as args.exe 1 2 3 4:
//
//args: [|"1"; "2"; "3"; "4"|]
//env.cmdline: [|"args.exe"; "1"; "2"; "3"; "4"|]