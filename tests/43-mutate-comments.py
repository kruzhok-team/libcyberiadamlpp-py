#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The comments mutation test
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
    d = CyberiadaML.Document(CyberiadaML.geometryFormatQt)
    sm = d.new_state_machine("sm1", "SM")
    s1 = d.new_state(sm, "s1", "State 1", CyberiadaML.Action(CyberiadaML.actionEntry, "init();"))
    s2 = d.new_state(sm, "s2", "State 2")

    # the comment factories
    c1 = d.new_comment(sm, "The first comment", CyberiadaML.Rect(0, 0, 100, 40))
    c2 = d.new_comment(sm, "note2", "The second comment", CyberiadaML.Rect(0, 60, 100, 40))
    c3 = d.new_comment(sm, "c3", "note3", "The third comment", CyberiadaML.Rect(0, 120, 100, 40))
    assert c3.get_id() == "c3"
    f1 = d.new_formal_comment(sm, "key/ value")
    f2 = d.new_formal_comment(sm, "formal2", "key2/ value2")
    f3 = d.new_formal_comment(sm, "f3", "formal3", "key3/ value3")
    assert f1.is_machine_readable()
    assert f2.is_machine_readable()
    assert f3.get_id() == "f3"
    assert f3.is_machine_readable()

    # the comment subjects
    sub1 = d.add_comment_to_element(c1, s1, CyberiadaML.Point(0, 0), CyberiadaML.Point(10, 10))
    sub2 = d.add_comment_to_element(c1, s2, "subj2")
    assert sub2.get_id() == "subj2"
    pl = CyberiadaML.Polyline()
    pl.append(CyberiadaML.Point(1, 2))
    pl.append(CyberiadaML.Point(3, 4))
    sub3 = d.add_comment_to_element_name(c2, s1, "State", CyberiadaML.Point(1, 2),
                                         CyberiadaML.Point(3, 4), pl)
    sub4 = d.add_comment_to_element_name(c2, s2, "ate", "subj4")
    sub5 = d.add_comment_to_element_body(c3, s1, "init")
    sub6 = d.add_comment_to_element_body(c3, s2, "nit", "subj6")
    assert sub1.get_type() == CyberiadaML.commentSubjectElement
    assert sub3.get_type() == CyberiadaML.commentSubjectName
    assert sub3.has_fragment()
    assert sub3.has_geometry_polyline()
    assert sub5.get_type() == CyberiadaML.commentSubjectData
    assert sub6.get_id() == "subj6"
    assert c1.has_subjects()
    assert len(c1.get_subjects()) == 2

    # the subject reference
    cs = sub3
    assert cs.get_id() == sub3.get_id()
    assert cs.get_fragment() == "State"
    print(repr(cs))

    # the comment body update
    c1.set_body("The updated comment")
    assert c1.get_body() == "The updated comment"

    # commenting the state machine is not allowed
    try:
        d.add_comment_to_element(c1, sm)
        exit(1)
    except CyberiadaML.ParametersException:
        pass

    print(d)
    CyberiadaML.LocalDocument(d, sys.argv[0] + ".graphml").save()

    # the subject removal
    c2.remove_subject(CyberiadaML.commentSubjectName, "State")
    assert len(c2.get_subjects()) == 1
    assert c2.get_subjects()[0].get_fragment() == "ate"
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
