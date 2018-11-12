%%%-------------------------------------------------------------------
%% @doc skolenie top level supervisor.
%% @end
%%%-------------------------------------------------------------------

-module(skolenie_sup).

-behaviour(supervisor).

-export([start_link/0]).

-export([init/1]).

-define(SERVER, ?MODULE).

start_link() ->
    supervisor:start_link({local, ?SERVER}, ?MODULE, []).

init([]) ->
    SupFlags = #{strategy => one_for_all,
                 intensity => 0,
                 period => 1},
    ChildSpecs = [
    	task2_server_spec()
    ],
    {ok, {SupFlags, ChildSpecs}}.

task2_server_spec() ->
  
    #{
        id          => task2_server,
        start       => {
                            task2_server,
                            start_link, 
                            []
                        },
        restart     => permanent,
        shutdown    => timer:seconds(10),
        type        => worker,
        modules     => [task2_server]
    }.

