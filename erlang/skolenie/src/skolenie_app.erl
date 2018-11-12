%%%-------------------------------------------------------------------
%% @doc skolenie public API
%% @end
%%%-------------------------------------------------------------------

-module(skolenie_app).

-behaviour(application).

-export([start/2, stop/1]).

start(_StartType, _StartArgs) ->
    skolenie_sup:start_link().

stop(_State) ->
    ok.
