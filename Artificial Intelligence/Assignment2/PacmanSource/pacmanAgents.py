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
import math


class RandomAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return

    # GetAction Function: Called with every frame
    def getAction(self, state):
        # get all legal actions for pacman
        actions = state.getLegalPacmanActions()
        # returns random action from all the valide actions
        return actions[random.randint(0, len(actions) - 1)]


class RandomSequenceAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        self.actionList = []
        for i in range(0, 10):
            self.actionList.append(Directions.STOP)
        return

    # GetAction Function: Called with every frame
    def getAction(self, state):
        # get all legal actions for pacman
        possible = state.getAllPossibleActions()
        for i in range(0, len(self.actionList)):
            self.actionList[i] = possible[random.randint(0, len(possible) - 1)]
        tempState = state
        for i in range(0, len(self.actionList)):
            if tempState.isWin() + tempState.isLose() == 0:
                tempState = tempState.generatePacmanSuccessor(
                    self.actionList[i])
            else:
                break
        # returns random action from all the valide actions
        return self.actionList[0]


class HillClimberAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return

    # GetAction Function: Called with every frame
    def getAction(self, state):
        next_seq = []
        next_action = state.getAllPossibleActions()
        for i in range(5):
            next_seq.append(random.choice(next_action))
        best = [gameEvaluation(state, state), [Directions.STOP]]
        while True:
            next_nb = []
            for i in range(len(next_seq)):
                # 50% chance to be changed into random action
                if random.randint(0, 1) == 0:
                    next_nb.append(random.choice(next_action))
                else:
                    next_nb.append(next_seq[i])
            cur_state = state
            for action in next_nb:
                next_state = cur_state.generatePacmanSuccessor(action)

                if not next_state:
                    return random.choice(best[1])

                if next_state.isWin() == 0 and next_state.isLose() == 0:
                    cur_state = next_state
                    continue
                else:
                    if next_state.isWin():
                        return random.choice(best[1])
                    break
            next_score = gameEvaluation(state, cur_state)

            if next_score > best[0]:
                best[0] = next_score
                best[1] = []
            elif next_score < best[0]:
                continue

            best[1].append(next_nb[0])
            next_seq = next_nb


class GeneticAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        self.possible = state.getAllPossibleActions()
        return

    # GetAction Function: Called with every frame
    def getAction(self, state):
        self.actionList = []
        for i in range(8):
            self.actionList.append(self.get_random_action_sequece())
        best = [gameEvaluation(state, state), [Directions.STOP]]
        while True:
            score_list = []
            for action in self.actionList:
                temp_score = self.get_sequence_score(state, action)
                if temp_score == float("-inf"):
                    return random.choice(best[1])
                score_list.append((action, temp_score))

            score_list.sort(key=lambda x: x[1])
            if score_list[-1][1] > best[0]:
                best[0] = score_list[-1][1]
                best[1] = [score_list[-1][0][0]]
            elif score_list[-1][1] == best[0]:
                best[1].append(score_list[-1][0][0])

            choose_list = []
            new_sequence = []
            for i in range(8):
                choose_list += [self.actionList[i]] * (i + 1)
            for i in range(4):
                X = random.choice(choose_list)
                Y = random.choice(choose_list)
                if random.randint(1, 100) <= 70:
                    X, Y = self.crossstop(X, Y)
                new_sequence.append(X)
                new_sequence.append(Y)
            for i in range(8):
                if random.randint(1, 100) <= 10:
                    self.mutate(new_sequence[i])
            self.actionList = new_sequence[:]

    def mutate(self, chromosomes):
        pos1 = random.randint(0, len(chromosomes) - 1)
        pos2 = random.randint(0, len(self.possible) - 1)
        chromosomes[pos1] = self.possible[pos2]

    def crossstop(self, X, Y):
        result = [[], []]
        for i in range(2):
            for j in range(5):
                if random.randint(0, 1) == 0:
                    result[i].append(X[j])
                else:
                    result[i].append(Y[j])
        return result

    def get_sequence_score(self, state, actionList):
        temp_state = state
        for action in actionList:
            if temp_state.isWin() == 0 and temp_state.isLose() == 0:
                temp_state = temp_state.generatePacmanSuccessor(action)
                if not temp_state:
                    return float("-inf")
            else:
                break
        return gameEvaluation(state, temp_state)

    def get_random_action_sequece(self):
        temp_sequence = []
        for i in range(5):
            temp_sequence.append(self.possible[random.randint(
                0,
                len(self.possible) - 1)])
        return temp_sequence


class MCTSAgent(Agent):
    # Initialization Function: Called one time when the game starts
    def registerInitialState(self, state):
        return

    # GetAction Function: Called with every frame
    def getAction(self, state):
        self.state = state
        self.root = TreeNode(None, None)
        self.root.set_child(None)

        while True:
            if not self.tree_policy():
                break

        temp = -1
        for node in self.root.children:
            if node.visits > temp:
                action = node.action
                temp = node.visits
        return action

    def tree_policy(self):
        cur_node = self.root
        cur_state = self.state
        flag = True
        while flag:
            best_score = 0
            best_action = Directions.STOP
            actions = cur_state.getLegalPacmanActions()
            for action in actions:
                next_state = cur_state.generatePacmanSuccessor(action)
                if not next_state:
                    return False
                if next_state.isWin() == 0 and next_state.isLose() == 0:
                    next_node = cur_node.get_child(action)
                    if not next_node:
                        cur_node.set_child(action)
                        cur_node.get_child(action).update(
                            self.rool_out(next_state))
                        flag = False
                        break
                    else:
                        value = next_node.get_score()
                        if value > best_score:
                            best_score = value
                            best_action = action
                else:
                    break

            if not flag:
                break
            cur_state = cur_state.generatePacmanSuccessor(best_action)
            if not cur_state:
                return False
            cur_node = cur_node.get_child(best_action)
            if not cur_node:
                return False
        return True

    def rool_out(self, state):
        cur_state = state
        for i in range(5):
            if cur_state.isLose() == 0 and cur_state.isWin() == 0:
                action = random.choice(cur_state.getAllPossibleActions())
                successors = cur_state.generatePacmanSuccessor(action)
                if successors == None:
                    break
                cur_state = successors
            else:
                return gameEvaluation(self.state, cur_state)

        return gameEvaluation(self.state, cur_state)


class TreeNode():
    def __init__(self, action, parent):
        self.action = action
        self.children = []
        self.parent = parent
        self.reward = 0.0
        self.visits = 0

    def get_child(self, action):
        for child in self.children:
            if child.action == action:
                return child

    def set_child(self, action):
        child = TreeNode(action, self)
        self.children.append(child)

    def get_score(self):
        return self.reward / float(self.visits) + math.sqrt(
            2 * math.log(self.parent.visits) / float(self.visits))

    def update(node, reward):
        while node:
            node.visits += 1
            node.reward += reward
            node = node.parent
