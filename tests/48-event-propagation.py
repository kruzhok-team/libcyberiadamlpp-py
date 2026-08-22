#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The event propagation keywords test
# 
#  Copyright (C) 2026 Alexey Fedoseev <aleksey@fedoseev.net>
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program. If not, see https://www.gnu.org/licenses/
#  ----------------------------------------------------------------------------- 

import sys
import traceback
import CyberiadaML

try:
    d = CyberiadaML.LocalDocument()
    d.open(sys.argv[0] + "-input.graphml")

    sm = d.get_state_machines()[0]

    # the defer keyword is imported into the state action
    waiting = sm.find_element_by_id("n0")
    assert waiting is not None
    actions = waiting.get_actions()
    assert len(actions) == 2
    assert not actions[0].has_propagation()
    assert actions[1].has_propagation()
    assert actions[1].get_propagation() == CyberiadaML.eventPropagationDefer

    # the keywords are imported into the transition actions
    transitions = sm.get_transitions()
    assert len(transitions) == 4
    for t in transitions:
        a = t.get_action()
        if t.get_id() == "n0-n1":
            assert a.get_propagation() == CyberiadaML.eventPropagationPropagate
        elif t.get_id() == "n1-n2":
            assert a.get_propagation() == CyberiadaML.eventPropagationBlock
        elif t.get_id() == "n2-n0":
            assert a.get_propagation() == CyberiadaML.eventPropagationDefer
        else:
            assert not a.has_propagation()

    doc = CyberiadaML.Document(d)
    print(doc)

    # the keywords survive the save/load round trip
    saved = CyberiadaML.LocalDocument(d, sys.argv[0] + ".graphml")
    saved.save()
    d2 = CyberiadaML.LocalDocument()
    d2.open(sys.argv[0] + ".graphml")
    sm2 = d2.get_state_machines()[0]
    assert sm.check_isomorphism(sm2) == CyberiadaML.smiIdentical

    # the propagation difference is reported by the actions compare
    pd = CyberiadaML.Document()
    psm = pd.new_state_machine("SM")
    s1 = pd.new_state(psm, "State 1")
    s2 = pd.new_state(psm, "State 2")
    s1.add_action(CyberiadaML.Action("EVENT", "", "action();", CyberiadaML.eventPropagationBlock))
    s2.add_action(CyberiadaML.Action("EVENT", "", "action();", CyberiadaML.eventPropagationPropagate))
    f = s1.compare_actions(s2)
    assert f & CyberiadaML.adiffPropagation
    assert not (f & CyberiadaML.adiffNumber)
    assert not (f & CyberiadaML.adiffGuards)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
