class MonteCarlo(object):
    def __init__(self, board, **kwargs):
        # Takes an instance of a Board and optionally some keyword
        # arguments.  Initializes the list of game states and the
        # statistics tables.

        milliseconds = kwargs.get('calculation_ms', 10)
        self.calculation_time_ms = datatime.timedelta(milliseconds = milliseconds)

        # check that this amount of moves  
        self.max_moves = kwargs.get('max_moves', 10)


        self.board  = board
        self.states = [] 

    def update(self, state):
        # Takes a game state, and appends it to the history.
        self.states.append(state)

    def get_play(self):
        # Causes the AI to calculate the best move from the
        # current game state and return it.
        begin = datetime.datetime.utcnow()
        while datetime.datetime.utcnow() - begin < self.calculation_time_ms:
            self.run_simulation()

    def run_simulation(self):
        # Plays out a "random" game from the current position,
        # then updates the statistics tables with the result.

        states_copy = self.states[:]
        # get last state
        current_state = states_copy[-1]

        for _ in range(self.max_moves):

            legal_plays = self.board.legal_plays(states_copy)

            play = choice(legal_plays)
            new_state = self.board.next_state(state, play)
            states_copy.append(new_state)

            current_state = new_state

            winner = self.board.winner(states_copy)

            if winner:
                break