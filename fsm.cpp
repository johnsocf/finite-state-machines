//
// fsm.cpp
//

#include "fsm.hpp"

using namespace std;

FSM::FSM() {
  // TODO
  this->state = -1;
  this->default_state = -1;
}

int FSM::addState(string label, bool is_accept_state) {
  // TODO
  State* new_state = new State;
  new_state->label = label;
  new_state->accept = is_accept_state;
  new_state->failure_trans = -1;
  //new_state->trans;
  this->states.push_back(new_state);
  int state_list_length = this->states.size();
  cout << "state list length: " << this->states.size() << "\n";
  int index_of_new_state = state_list_length - 1;
  if (state_list_length == 1) {
      this->state = index_of_new_state;
      this->default_state = index_of_new_state;
  }
  return index_of_new_state;
}

int FSM::addState(string label) {
  // TODO
  return addState(label, false);
  //return 0;
}

int FSM::addTransition(int stateA, int stateB, 
		       int signal, string transLabel) {
  // this method's documentation is longer than the implementation. to
  // help out, I'm including the comments for my implementation.
  //
  // 1. if stateA or stateB is out of range for the states vector,
  // return -1.
    //cout << "states size: " << this->states.size() << "\n";
    //cout << "state A: " << stateA << "\n";
    //cout << "state B: " << stateB << "\n";
    cout << "SIGNAL ON INPUT: " << signal << "\n";
    if ((this->states.size() < stateA) || (this->states.size() < stateB)) {
        cout << "out of range returning -1 : \n";
        return -1;
    }
  //
  // 2. get the State* for stateA and look for a duplicate
  // transition. if the new transition is FAILURE_SIGNAL, only need to
  // check the state's `failure_trans`. if it is a regular signal,
  // need to look at each id in the state's `trans` vector. if there's
  // a duplicate, return -1.
    State* state_a = this->states[stateA];
    //cout << "state a trans size" << state_a->trans.size() << "\n";
    // if 'failure - check failure trans'
//    toDo: determine if new trans is a failure signal
    bool a_has_trans = false;
    if (state_a->trans.size() > 0) {
        for (int i=0; i< state_a->trans.size(); i++) {
            cout << "trans id in loop within specific state!" << state_a->trans[i] << "\n";
            if (state_a->trans[i] == signal) {
                cout << "duplicate found in trans set! \n";
                a_has_trans = true;
                //return -1;
            }
        }

//        toDo: check for duplicates - that's why tests failing...'
    }

    if (this->transitions.size() > 0) {
        for (int i=0; i< this->transitions.size(); i++) {
            //cout << "trans id in loop SET!!" << this->transitions[i]->signal << "\n";
            if (this->transitions[i]->signal == signal) {
                cout << "duplicate found in transitions SET! \n";
                cout << "has trans: " << a_has_trans << "\n";
                cout << "NEXT STATE: " << this->transitions[i]->next_state << "\n";
                cout << "state b: " << stateB << "\n";
                bool a_has_trans = false;
                if (state_a->trans.size() > 0) {
                    //state a at i... reverse.
                    //state_a->trans[i] ==
                    for (int j=0; j< state_a->trans.size(); j++) {
                        cout << "trans id in loop within specific state! " << state_a->trans[i] << "\n";
                        cout << " state A TRANS ARRAY VALUE : " << state_a->trans[j] << "\n";
                        if ((state_a->trans[j] == stateA) && (this->transitions[i]->next_state == stateB)) {
                            cout << "remove!!! \n";
                            return -1;
                        }
//                        if (state_a->trans[i] == signal) {
//                            cout << "duplicate found in trans set! \n";
//                            a_has_trans = true;
//                            //return -1;
//                        }
                    }

//                  toDo: check for duplicates - that's why tests failing...'
                }
//                if (a_has_trans && (transitions[i]->next_state == stateB)) {
//                    return -1;
//                }

            }
        }
    }


  //
  // 3. build a new Transition, and set its values.
    Transition* new_transition = new Transition;
    new_transition->label = transLabel;
    new_transition->signal = signal;
    new_transition->next_state = stateB;
  //
  // 4. add the new transition to the FSM and get its ID.
    this->transitions.push_back(new_transition);
    cout << "new state a trans size: " << this->transitions.size() << "\n";
    int new_transitions_id = this->transitions.size()-1;
    cout << "pushback to a: " << new_transitions_id << "\n";


  //
  // 5. using the State* from step 2, use the new transition ID to
  // either set the failure_trans or add to the trans list.
    state_a->trans.push_back(new_transitions_id);
    cout << "NEW TRANSITION ADDED: a,b: " << stateA << ", " << stateB << ", signal: " << signal << " label: " << transLabel << "\n";
  //
  // 6. return the new transition's ID.
    return new_transitions_id;

  // TODO
  return 0;
}

int FSM::countStates() {
  // TODO
    return this->states.size();
  //return 0;
}

int FSM::countTransitions() {
  // TODO
    return this->transitions.size();
  //return 0;
}

int FSM::getCurrentState() {
  // TODO
  cout << "current state: " << this->state << "\n";
  int i = this->state;
  //cout << this->states[i]->label << '\n';
  return this->state;
  //return 0;
}

bool FSM::isAcceptState() {
  // TODO
  bool current_state = false;
  int current_state_index = this->state;
  if (this->states.size() > 0) {
      State* pointer_to_current_state = this->states[current_state_index];
      current_state = pointer_to_current_state->accept;
  }
  return current_state;
}

State* FSM::getState(int id) {
  // TODO
  FSM* fsm = this;
  cout << "this id? " << id << " = " << fsm->states.size() << "\n";
  if (fsm->states.size() <= id) {
      return NULL;
  } else if (fsm->states[id] != NULL  && (fsm->states.size() > id)) {
        return fsm->states[id];
  }
//  if (fsm->states[id] == NULL) {
//      return NULL;
//  }
//  if (fsm->states[id] != NULL  && (fsm->states.size() > id)) {
//      //cout << "state size? " << id << " = " << fsm->states.size() << "\n";
//      return fsm->states[id];
//  } else {
//      return NULL;
//  }

}

Transition* FSM::getTransition(int id) {
  // TODO
    cout << "transition id: " << id << "\n";
    cout << "transition size: " << this->transitions.size() << "\n";
    if (id < this->transitions.size()) {
        return this->transitions[id];
    } else {
        return NULL;
    }


}

int FSM::getDefaultState() {
  // TODO
    return this->default_state;
  //return 0;
}

void FSM::setState(int id) {
    State* current_state = this->states[id];
    this->state = id;
  // TODO  
}

bool FSM::handleSignal(int signal) {
//    toDo: finish this first.
  // like addTransition, the documentation is longer than the
  // implementation. Here's my pseudocode:
  //
  // 1. If the FSM is currently in a bad state, return false.
    cout << "signal: " << signal << "\n";

    FSM* s = this;
    int state_index = s->getCurrentState();
    if (state_index == -1) {return false;}
    State* current_state = s->states[state_index];
    cout << "get current state: " << s->getCurrentState() << "\n";
    State* state_detail;
    cout << 'state index' << state_index << "\n";
    cout << 'state size' << s->states.size() << "\n";


  // 2. Iterate through the current state's normal transitions and
  // look for one that has the same signal as the one given to the
  // method.
  bool found = false;
    for (int i=0; i<state_detail->trans.size() - 1; i++) {
        int transition_index = state_detail->trans[i];
        Transition* this_transition = s->transitions[transition_index];
        int signal = this_transition->signal;

        cout << "many signals: " << signal << "\n";
        if (this_transition->signal == signal) {
            //if
            found = true;
            this->state = this_transition->next_state;
            return true;
        }
    }
//
//  if (!found) {
//        if (state_detail->failure_trans > 0) {return false;}
//        //else {}
//  }
  //
  // 3. If there wasn't a normal transition, see if there was a
  // failure_trans transition for the state. If not, return false.
  //
  // 4. If there was a normal or a failure transition, update the FSM
  // to be in the next_state indicated by that transition, and return
  // true.

  // TODO
  return false;
}

ostream &operator << (ostream& out, FSM* fsm) {
  int c = 0;
  for (auto it=fsm->states.begin(); it != fsm->states.end(); ++it) {
    out << "  state " << c << ": " << *it << endl;
    c++;
  }
  c = 0;
  for (auto it=fsm->transitions.begin(); it != fsm->transitions.end(); ++it) {
    out << "  trans " << c << ": " << *it << endl;
    c++;
  }
  out << "  current state: " << fsm->state;
  if (fsm->isAcceptState()) {
    out << " (accepting state!)";
  }
  out << endl;
  return out;
}

ostream &operator << (ostream& out, Transition* tr) {
  if (tr == NULL) {
    out << "Transition NULL";
  } else {
    out << "\"" << tr->label << "\" (" << tr->signal << ") --> " << tr->next_state;
  }
  return out;
}

ostream &operator << (ostream& out, State* st) {
  if (st == NULL) {
    out << "State: NULL";
  } else {
    out << "State: " << st->label;
    if (st->accept) {
      out << " +";
    }
  }
  return out;
}
