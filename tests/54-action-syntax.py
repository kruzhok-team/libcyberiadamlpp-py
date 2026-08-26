#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The action syntax test
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
    d.open(sys.argv[0] + "-input.graphml", CyberiadaML.formatCyberiada10,
           CyberiadaML.geometryFormatNone)
    sm = d.get_state_machines()[0]
    s = sm.find_element_by_id("n0")
    assert s
    actions = s.get_actions()
    assert len(actions) == 3

    # the defer keyword follows the action separator (6.8)
    assert actions[0].get_trigger() == "TICK"
    assert actions[0].get_propagation() == CyberiadaML.eventPropagationDefer
    assert actions[0].get_behavior() == "count();"

    # the keyword before the separator is accepted as well
    assert actions[1].get_trigger() == "TOCK"
    assert actions[1].get_propagation() == CyberiadaML.eventPropagationDefer

    # the event name may be empty
    assert not actions[2].has_trigger()
    assert actions[2].get_behavior() == "plain();"

    # the escaped brackets are kept in the guard
    t = sm.find_element_by_id("t0")
    assert t
    assert t.get_action().get_guard() == "a \\[b\\] c"

    print(CyberiadaML.Document(d))

    # the canonical form is written back and read again
    CyberiadaML.LocalDocument(d, sys.argv[0] + ".graphml").save()
    d2 = CyberiadaML.LocalDocument()
    d2.open(sys.argv[0] + ".graphml", CyberiadaML.formatCyberiada10,
            CyberiadaML.geometryFormatNone)
    s2 = d2.get_state_machines()[0].find_element_by_id("n0")
    assert s2
    assert s2.get_actions()[1].get_propagation() == CyberiadaML.eventPropagationDefer
    assert sm.check_isomorphism(d2.get_state_machines()[0], False) == CyberiadaML.smiIdentical
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
