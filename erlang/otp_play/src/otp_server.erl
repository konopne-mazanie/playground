%%%-------------------------------------------------------------------
%%% @author Peter Uhrecky
%%% @copyright (C) 2019, <Siemens>
%%% @doc
%%%
%%% @end
%%% Created : 23. júl 2019 16:25
%%%-------------------------------------------------------------------
-module(otp_server).
-behaviour(gen_server).
-import(play, [start_service/0, stop_service/1, save_to_service/2, pop_from_service/2]).
-export([start_link/0, pop_item/2, add_item/2, stop/1]).
-export([init/1, handle_call/3, handle_cast/2, handle_info/2,
  terminate/2, code_change/3]).

%%% Client API
start_link() ->
  gen_server:start_link(?MODULE, [], []).

%% Synchronous pop item
pop_item(Pid, Data) ->
  gen_server:call(Pid, {pop, Data}).

%% Asynchronous add item
add_item(Pid, Data) ->
  gen_server:cast(Pid, {add, Data}).

%% Terminate server
stop(Pid) ->
  gen_server:call(Pid, terminate).

%%% Initialize
init([]) ->
  {ok, start_service()}.

handle_call({pop, Data}, _From, StoragePid) ->
  {reply, pop_from_service(StoragePid, Data)};
handle_call(terminate, _From, StoragePid) ->
  {stop, normal, ok, StoragePid}.

handle_cast({add, Data}, StoragePid) ->
  save_to_service(StoragePid, Data),
  {noreply, StoragePid}.

handle_info(Msg, StoragePid) ->
  io:format("Unexpected message: ~p~n",[Msg]),
  {noreply, StoragePid}.

terminate(normal, StoragePid) ->
  stop_service(StoragePid),
  ok.

code_change(_OldVsn, State, _Extra) ->
  {ok, State}.