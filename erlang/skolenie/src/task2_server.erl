-module(task2_server).
-behaviour(gen_server).
-export([start_link/0]).

-export([init/1,
         handle_call/3,
         handle_cast/2,
         handle_info/2,
         terminate/2,
         code_change/3]).

-record(state, {}).

start_link() ->
    gen_server:start_link({local, ?MODULE}, ?MODULE, [], []).
%%=============================================================
init([]) ->
    timer:send_after(timer:seconds(1), main_loop),
    {ok, #state{}}.
%%=============================================================
handle_call(_Request, _From, State) ->
    {reply, ignored, State}.

handle_cast(_Msg, State) ->
    {noreply, State}.
%%=============================================================
handle_info(main_loop, State) ->
    main_loop(),
    {noreply, State};
handle_info(_Info, State) ->
    {noreply, State}.
%%=============================================================
terminate(_Reason, _State) ->
    ok.

code_change(_OldVsn, State, _Extra) ->
    {ok, State}.
%%=============================================================
main_loop() ->
    FindPriceSingleFun  = fun(Command) -> task2:find_price(task2:parse_file("test_file.csv"), Command) end,
    FindPriceMultiFun   = fun(Commands) ->  task2:get_products(FindPriceSingleFun, Commands) end,
    io:format("~p~n", [task2:handle_command(fun(Products) -> task2:display_price_multiple(Products) end,
        FindPriceMultiFun, task2:get_barcode())]),
    timer:send_after(timer:seconds(1), main_loop).
