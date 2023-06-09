# Pente
In this project, we will implement agent that plays the game of Pente, the two-player version of the abstract strategy board game. It is in the m,n,k-game family from which tic-tac-toe (3,3,3) and Connect Four also come from, where the players are trying to connect k pieces on the board before the other player does. Pente stands out from these games because it includes a piece capture mechanic, where the player can sandwich a pair of their opponent’s pieces and capture them. It is played on a 19x19 board, where pieces are placed on the intersection of the lines (like the game Go). White always opens the game (like in Chess). 

The players take turns putting pieces on the board until:
1) A player connects 5 of their pieces in a horizontal, vertical or a diagonal line, OR
2) A player makes 5 total captures (equals to 10 pieces of their opponent’s since pieces can only be captured in pairs).

The custodial capture mechanic, where a player flanks the opponent’s pieces with their own to capture them, only applies to pairs of the opponent’s pieces. Therefore, if the current board formation is XOO_ and player X plays their piece as XOOX, the O pieces are captured and the board becomes X_ _X. Note again that this only works for pairs of pieces, therefore X cannot capture their opponent’s pieces from a board like XOOO_ or XO_.

Captures only happen when a capturing piece is placed. Therefore, if the board is XO_X and O places a piece in the free intersection, the board formation becomes XOOX and no capture happens by X.

More details on the game can be found at https://en.wikipedia.org/wiki/Pente and we will also go over the gameplay for you below (be careful, Wikipedia images show a 13x13 board). If you would like to try the game of Pente to understand the general gameplay, you can utilize the “Play the AI” option without having to log in at https://pente.org/join.jsp. Note that these resources are just for you to familiarize yourself with the game, you should strictly follow the rules we outline below while coding your game-playing agent (there are several variants of the game).

