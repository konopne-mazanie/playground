%%% @author Peter Uhrecky
%%% @copyright (C) 2019, <Siemens>
%%% @doc
%%%
%%% @end
%%% Created : 23. júl 2019 16:25
%%%-------------------------------------------------------------------
-module(play).
-export([start/0, store/1, start_service/0, stop_service/1, save_to_service/2, pop_from_service/2]).

-record(developer, {name = "", project = "", languages = []}).

start() ->
%%    io:fwrite("Hello world3\n"),
%%    {ok, [Input]} = io:fread("Enter record: ", "~d"),
%%    io:format("You entered: ~w\n", [Input]),
%%    io:format("Added 1 ~w~n", [add1(Input)]),
%%
%%    io:format("rangeFor List: ~w~n", [rangeFor2(2,5)]),
%%
%%    Condition = fun(Params) ->
%%        {X, Y} = Params,
%%        (X < Y) end,
%%    Function = fun(Params) ->
%%        io:format("While cycle fn running, params: ~w~n", [Params]),
%%        {X, Y} = Params,
%%        {X+1, Y} end,
%%    while(Condition, {1,5}, Function),
%%
%%    printToFile("test.txt", "teststring"),
%%
%%    runLoop(),
%%
%%    printParsedList(),
%%
%%    packBinary(),
%%
%%    test_storage(),
%%
%%    monitor_storage(),

    io:fwrite("end").

%% Simple Add
add1(Number) when Number > 0 ->
    Number + 1.

%% For loop adding to list
rangeFor2(Start, Stop) -> rangeFor(Start, Stop, []).
rangeFor(Start, Start, Acc) -> Acc;
rangeFor(Start, Stop, Acc) when Stop > Start ->
    rangeFor(Start+1, Stop, [Start|Acc]).

%% While loop with lambdas
while(Condition, Params, Function) ->
    Test = Condition(Params),
    if
        Test ->
            while(Condition, Function(Params), Function);
        true ->
            ok
    end.

%% Output to file
-spec play:testFNameEmpty(string()) -> ok | nok. %function types definition
testFNameEmpty(Filename) ->
    if
        Filename =:= "" ->
            nok;
        true ->
            ok
    end.
printToFile1(ok, Filename, Term) ->
    io:fwrite("Printing to file~n"),
    {ok, File} = file:open(Filename, [write]),
    file:write(File, Term);
printToFile1(nok, _, _) -> noprint.
printToFile(Filename, Term) -> printToFile1(testFNameEmpty(Filename), Filename, Term).

%% Concurrency communication
loop() ->
    receive
        continue ->
            io:fwrite("continuing loop~n"),
            loop();
        stop ->
            io:fwrite("Stopping loop~n"),
            stop
    end.

runLoop() ->
    Proccess = spawn(fun() -> loop() end),
    Proccess ! continue,
    io:fwrite("between loop~n"),
    Proccess ! stop.

%% record(struct) usage, maps
defineList() ->
    List = [
        {name, "Dev"},
        {project, "MSIB"},
        {languages, [
            "JS", "Python", "Ruby"
        ]}
    ].
-type myMap() :: #{name => string(), project => string(), languages => [string()]}.
-spec play:printParsedList() -> myMap().
printParsedList() ->
    List = defineList(),
    [{name, Name},
        {project, Project},
        {languages, Languages}] = List,
    ExtractedPerson = #developer{name = Name, project = Project, languages = Languages},
    MyMap = maps:from_list(List),
    io:format("Developer name is: ~p~n", [maps:get(name, MyMap)]),
    MyMap.

%% Comprehensions
doubleizeListElems(List) ->
    [2*Elem || Elem <- List].
returnOnlyEven(List) ->
    [Elem || Elem <- List, Elem rem 2 =:= 0].
returnOnlyEvenAdd1(List) ->
    [Elem+1 || Elem <- List, Elem rem 2 =:= 0].

%% Binaries
packBinary() ->
    Number = 125,
    Bin = integer_to_binary(Number),
    <<B1:8, B2:8, B3:8>> = Bin,
    io:format("24bit integer divided into 3 8 bit sections: 1: ~w, 2: ~w, 3: ~w", [B1, B2, B3]),
    NumberAgain = [ {A1,A2,A3} || <<A1:8,A2:8,A3:8>> <= Bin ].

%%Data storing process
store(Storage) ->
    receive
        {Sender, {save, Data}} ->
            Sender ! {self(), ok},
            store([Data|Storage]);
        {Sender, {pop, Data}} ->
            case lists:member(Data, Storage) of
                true ->
                    Sender ! {self(), ok},
                    store(lists:delete(Data, Storage));
                false ->
                    Sender ! {self(), not_found},
                    store(Storage)
            end;
        {Sender, terminate} ->
            if
                length(Sender) > 0 ->
                    Sender ! {self(), not_empty},
                    store(Storage);
                true ->
                    Sender ! {self(), ok}
            end
    end.

start_service() ->
    spawn(?MODULE, store, [atom]).

stop_service(Pid) ->
    Pid ! {self(), terminate},
    receive
        {Pid, Response} ->
            Response
    end.
save_to_service(Pid, Data) ->
    Pid ! {self(), {save, Data}},
    receive
        {Pid, Response} ->
            Response
    after 10000 ->
        timeout
    end.
pop_from_service(Pid, Data) ->
    Pid ! {self(), {pop, Data}},
    receive
        {Pid, Response} ->
            Response
    end.

test_storage_inner() ->
    Pid = start_service(),
    Data = "Testing data",
    case save_to_service(Pid, Data) of
        ok ->
            io:format("Data saved~n");
        nok ->
            io:format("Error occured~n");
        timeout ->
            io:format("Error timeout~n")
    end,
    case pop_from_service(Pid, Data) of
        ok ->
            io:format("Data removed~n");
        not_found ->
            io:format("Data not found~n")
    end,
    case stop_service(Pid) of
        ok ->
            io:format("Service stopped~n");
        not_empty ->
            throw(bad_service_exit)
    end.

test_storage() ->
    try test_storage_inner()
    catch
        bad_service_exit ->
            io:format("Error: Bad service exit catched~n")
    end.

%% Monitors and Links
monitor_storage() ->
    Pid = start_service(),
    Reference = erlang:monitor(process, Pid),
    spawn(fun() -> timer:sleep(5000), stop_service(Pid) end),
    receive
        {Tag, Reference, process, Pid, Reason} ->
            io:format("Something happend with process: ~w~n", [{Tag, Reference, process, Pid, Reason}])
    end.
