-module(task1_tests).
-include_lib("eunit/include/eunit.hrl").

-define(PRINT, true).
%%=========================================================
notZeroPlusZero_test() ->
	A = {1, 1},
	B = {0, 0},
	?assertEqual({1, 1}, task1:sum(A, B)).
%%---------------------------------------------------------
zeroPlusZero_test() ->
	A = {0, 0},
	B = {0, 0},
	?assertEqual({0, 0}, task1:sum(A, B)).
%%---------------------------------------------------------
zeroPlusNotZero_test() ->
	A = {0, 0},
	B = {1, 2},
	?assertEqual({1, 2}, task1:sum(A, B)).
%%---------------------------------------------------------
equalSum_test() ->
	A = {1, 3},
	B = {1, 3},
	?assertEqual({2, 3}, task1:sum(A, B)).
%%---------------------------------------------------------
sameDenominator_test() ->
	A 									= {2, 3},
	B 									= {1, 3},
	
	{A_Num, Denominator}				= A,
	{B_Num, _} 							= B,

	{Res_Numerator, Res_Denominator} 	= task1:sum(A, B),

	?assertEqual(A_Num + B_Num, Res_Numerator),
	?assertEqual(Denominator, Res_Denominator).
%%---------------------------------------------------------
sameDenominatorEquals_test() ->
	A = {2, 3},
	B = {1, 3},

	?assert(task1:fraction_equals({3, 3}, task1:sum(A, B))).