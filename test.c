1 begin_block p _ _
2 end_block p _ _
3 begin_block f _ _
4 + 0 1 T_1
5 + 9 0 T_2
6 < T_1 T_2 8
7 jump _ _ 9
8 jump _ _ 4
9 < a b 11
10 jump _ _ 13
11 := 0 _ k
12 jump _ _ 14
13 := 9 _ l
14 out _ _ a
15 := 0 _ a
16 < a b 15
17 jump _ _ 18
18 end_block f _ _
19 begin_block x _ _
20 end_block x _ _
