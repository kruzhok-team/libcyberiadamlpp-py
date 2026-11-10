#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The test of the revision diff of two documents and of two state machines
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

FLAG_NAMES = ["added", "removed", "type", "title", "actions", "parent", "link", "comment", "color",
              "geometry", "collapsed", "source", "target", "trigger", "guard", "behavior",
              "propagation", "subject", "meta", "elements"]
KIND_NAMES = ["node", "transition", "link"]


def flags_str(flags):
    return "".join(" " + name for i, name in enumerate(FLAG_NAMES) if flags & (1 << i))


def side(ident):
    return ident if ident else "-"


def show(d):
    print("document:" + flags_str(d.flags))
    for m in d.meta:
        print(" meta {}: {} -> {}".format(m.name, m.first if m.in_first else "-",
                                         m.second if m.in_second else "-"))
    for sm in d.machines:
        print(" sm {} {}:{}".format(side(sm.first), side(sm.second), flags_str(sm.flags)))
        for e in sm.elements:
            if not e.flags:
                continue
            line = "  {} {} {}:{}".format(KIND_NAMES[e.kind], side(e.first), side(e.second), flags_str(e.flags))
            if e.kind == CyberiadaML.diffKindCommentLink:
                line += " (comment {})".format(side(e.second_comment or e.first_comment))
            print(line)


try:
    before = CyberiadaML.LocalDocument()
    before.open(sys.argv[0] + "-before.graphml")
    after = CyberiadaML.LocalDocument()
    after.open(sys.argv[0] + "-after.graphml")

    same = before.diff(before)
    assert not same.changed()
    assert len(same.machines) == 1 and not same.machines[0].changed()

    print("== the edited revision")
    d = before.diff(after)
    assert d.changed() and d.flags & CyberiadaML.diffMeta
    show(d)

    print("== with the geometry")
    show(before.diff(after, CyberiadaML.DiffOptions(geometry=True)))

    print("== without the comments")
    show(before.diff(after, CyberiadaML.DiffOptions(comments=False)))

    print("== a new document")
    added = CyberiadaML.Document().diff(after)
    assert len(added.machines) == 1 and added.machines[0].flags & CyberiadaML.diffAdded
    assert all(e.added() for e in added.machines[0].elements)
    print("elements added:", len(added.machines[0].elements))

    print("== the state machines")
    smd = before.get_state_machines()[0].diff(after.get_state_machines()[0])
    assert smd.changed() and smd.flags & CyberiadaML.diffElements
    print("sm {} {}:{}".format(smd.first, smd.second, flags_str(smd.flags)))
except Exception:
    traceback.print_exc()
    sys.exit(1)
