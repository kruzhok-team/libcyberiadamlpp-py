#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
#
#  The submachine states and entry/exit points test
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
    d = CyberiadaML.Document()

    # the referenced machine
    worker = d.new_state_machine("Worker")
    d.new_state(worker, "Run")

    # the caller with a submachine state and connection points (8.1)
    sm = d.new_state_machine("Caller")
    d.new_state(sm, "After")
    # entry/exit points standalone at the SM level (8.3.2)
    d.new_entry(sm, "SM in", CyberiadaML.Point(5, 5))
    d.new_exit(sm, "SM out", CyberiadaML.Point(15, 15))
    sub = d.new_submachine_state(sm, worker.get_id(), "Nested", CyberiadaML.Rect(0, 0, 80, 40))
    assert sub.is_submachine_state()
    assert sub.get_submachine_reference() == worker.get_id()
    # the connection points bound to the referenced machine, on the state border
    d.new_entry(sub, "Start", CyberiadaML.Point(-40, 0))
    d.new_exit(sub, "Done", CyberiadaML.Point(40, 0))
    # the nested points do not reclassify the state into a composite one
    assert sub.get_type() == CyberiadaML.elementSubmachineState

    path = sys.argv[0] + ".graphml"
    print(d)
    CyberiadaML.LocalDocument(d, path).save()
    # the submachine reference and its connection points reload intact
    reloaded = CyberiadaML.LocalDocument()
    reloaded.open(path)
    print(reloaded)
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
