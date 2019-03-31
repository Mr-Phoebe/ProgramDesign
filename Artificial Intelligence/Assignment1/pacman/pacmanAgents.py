# pacmanAgents.py
# ---------------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


from pacman import Directions
from game import Agent
from heuristics import *
import random

class RandomAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return;

    # GetAction Function: Called with every frame
    def getAction(self, state):
        # get all legal actions for pacman
        actions = state.getLegalPacmanActions()
        # returns random action from all the valide actions
        return actions[random.randint(0,len(actions)-1)]

class OneStepLookAheadAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return;

    # GetAction Function: Called with every frame
    def getAction(self, state):
        # get all legal actions for pacman
        legal = state.getLegalPacmanActions()
        # get all the successor state for these actions
        successors = [(state.generatePacmanSuccessor(action), action) for action in legal]
        # evaluate the successor states using scoreEvaluation heuristic
        scored = [(admissibleHeuristic(state), action) for state, action in successors]
        # get best choice
        bestScore = min(scored)[0]
        # get all actions that lead to the highest score
        bestActions = [pair[1] for pair in scored if pair[0] == bestScore]
        # return random action from the list of the best actions
        return random.choice(bestActions)

class BFSAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return;

    # GetAction Function: Called with every frame
    def getAction(self, state):
        que = []
        nextActions = {}

        legal = state.getLegalPacmanActions()
        successors = [(state.generatePacmanSuccessor(action), action) for action in legal]
        for successor in successors:
            nextActions[successor[0]] = successor[1]
            que.insert(0, (successor[0], admissibleHeuristic(successor[0])))

        while len(que) != 0:
            curStatus = que[-1][0]
            que.pop()

            curLegal = curStatus.getLegalPacmanActions()
            curSuccessors = [curStatus.generatePacmanSuccessor(action) for action in curLegal]

            for successor in curSuccessors:
                if not successor:
                    return nextActions[min(que, key = lambda x : x[1])[0]]
                if successor.isWin():
                    return nextActions[curStatus]
                elif successor.isLose():
                    continue
                nextActions[successor] = nextActions[curStatus]
                que.insert(0, (successor, admissibleHeuristic(successor)))
        return Directions.STOP

class DFSAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return;

    # GetAction Function: Called with every frame
    def getAction(self, state):
        stack = []
        nextActions = {}

        legal = state.getLegalPacmanActions()
        successors = [(state.generatePacmanSuccessor(action), action) for action in legal]
        for successor in successors:
            nextActions[successor[0]] = successor[1]
            stack.append((successor[0], admissibleHeuristic(successor[0])))

        while len(stack) != 0:
            curStatus = stack[-1][0]
            stack.pop()

            curLegal = curStatus.getLegalPacmanActions()
            curSuccessors = [curStatus.generatePacmanSuccessor(action) for action in curLegal]

            for successor in curSuccessors:
                if not successor:
                    return nextActions[min(stack, key = lambda x : x[1])[0]]
                if successor.isWin():
                    return nextActions[curStatus]
                elif successor.isLose():
                    continue
                nextActions[successor] = nextActions[curStatus]
                stack.append((successor, admissibleHeuristic(successor)))
        return Directions.STOP


class AStarAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return;

    # GetAction Function: Called with every frame
    def getAction(self, state):
        que = []
        nextActions = {}

        legal = state.getLegalPacmanActions()
        successors = [(state.generatePacmanSuccessor(action), action) for action in legal]
        for successor in successors:
            nextActions[successor[0]] = (successor[1], 1)
            que.append((successor[0], admissibleHeuristic(successor[0]) + nextActions[successor[0]][1]))

        while len(que) != 0:
            curNode = min(que,key= lambda x : x[1])
            curStatus = curNode[0]
            que.remove(curNode)

            curLegal = curStatus.getLegalPacmanActions()
            curSuccessors = [curStatus.generatePacmanSuccessor(action) for action in curLegal]

            for successor in curSuccessors:
                if not successor:
                    return nextActions[min(que, key = lambda x : x[1])[0]][0]
                if successor.isWin():
                    return nextActions[curStatus]
                elif successor.isLose():
                    continue
                nextActions[successor] = (nextActions[curStatus][0], nextActions[curStatus][1] + 1)
                que.append((successor, admissibleHeuristic(successor) + nextActions[successor][1]))
        return Directions.STOP
