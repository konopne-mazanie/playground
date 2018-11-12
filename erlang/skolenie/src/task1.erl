-module(task1).
-compile(export_all).

-type fraction() :: {integer(), integer()}.
%%=========================================================
-spec sum(fraction(), fraction()) -> fraction().
sum({0, 0}, B) ->
	B;
sum(A, {0, 0}) ->
	A;
sum({A, Denom}, {B, Denom}) ->
	{A + B, Denom};
sum(A, B) ->
	{A1, A2} = A,
	{B1, B2} = B,
	{(A1*B2) + (B1*A2), (B1*B2)}.
%%=========================================================
-spec fraction_equals(fraction(), fraction()) -> boolean().
fraction_equals(A, B) ->
	{A1, A2}	= A,
	{B1, B2}	= B,
	A_Float		= A1/A2,
	B_Float		= B1/B2,

	A_Float =:= B_Float.