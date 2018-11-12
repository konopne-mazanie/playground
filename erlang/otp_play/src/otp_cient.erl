%%%-------------------------------------------------------------------
%%% @author Peter Uhrecky
%%% @copyright (C) 2019, <Siemens>
%%% @doc
%%%
%%% @end
%%% Created : 23. júl 2019 16:25
%%%-------------------------------------------------------------------
-module(otp_cient).
-import(otp_server, [start_link/0, pop_item/2, add_item/2, stop/1]).
-export([start/0]).

start() ->
  Pid = case start_link() of
    {ok, Pd} ->
      Pd;
    _ ->
      error_starting_link
  end,
  if
    Pid =:= error_start_link ->
      exit(error_start_link);
    true ->
      ok
  end,
  Data = "testing data",
  add_item(Pid, Data),
  pop_item(Pid, Data),
  stop(Pid).