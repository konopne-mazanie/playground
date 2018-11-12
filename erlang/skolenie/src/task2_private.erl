-module(task2_private).
-include("task2_types.hrl").
-compile(export_all).

%%=========================================================
-spec format_price(integer()) -> string().
format_price(Price) when is_number(Price)	->
	integer_to_list(Price).
%%=========================================================
-spec parse_commalist(string()) -> list(string()).
parse_commalist(Input) ->
	Compiled = [re:run(Barcode, "\\w+", [global, {capture, [0], list}]) || Barcode <- string:tokens(Input, ",")],
	[hd(hd(MatchList)) || {match, MatchList} <- Compiled].
%%=========================================================
-spec parse_line(string()) -> product().
parse_line(Line) ->
	[Barcode, Price] = parse_commalist(Line),
	parse_line_continue(Barcode, list_to_integer(Price)).
%%---------------------------------------------------------
parse_line_continue([], Price)		-> 	throw(empty_barcode);
parse_line_continue(Barcode, Price) ->	{Barcode, Price}.
%%=========================================================
for_each_line(Device) ->
	case io:get_line(Device, "") of
		eof		-> [];
		Line 	-> for_each_line([parse_line(Line)], Device)
	end.
%%---------------------------------------------------------
for_each_line(Products, Device) ->
	case io:get_line(Device, "") of
		eof		-> Products;
		Line 	-> for_each_line([parse_line(Line) | Products], Device)
	end.