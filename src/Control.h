namespace control {
    enum Move {
        None,
        Fall,
        Left,
        Right
    };

    Move getMove(bool& loop);
}