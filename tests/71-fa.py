#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
#
#  The EXT-FA documents: the automaton flag, the alphabets, the FA exception
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


def open_document(path, strict):
    d = CyberiadaML.LocalDocument()
    d.open(path, CyberiadaML.formatCyberiada10, CyberiadaML.geometryFormatNone,
           False, False, False, False, False, strict)
    return d


try:
    prefix = sys.argv[0] + "-"

    # a valid automaton: the flag and the alphabet comments
    valid = open_document(prefix + "valid.graphml", True)
    assert valid.is_fa()
    assert valid.has_input_alphabet()
    assert valid.get_input_alphabet().get_name() == "FA_INPUT"
    assert valid.get_input_alphabet().get_body() == "0\n1"
    assert valid.has_output_alphabet()
    assert valid.get_output_alphabet().get_name() == "FA_OUTPUT_RE"

    # a transition with a guard is refused in both modes with the FA exception
    for strict in (False, True):
        try:
            open_document(prefix + "invalid.graphml", strict)
            exit(1)
        except CyberiadaML.FAException as e:
            assert str(e).startswith('FA Exception')

    # the same document without type/ fa is an ordinary state machine
    plain = open_document(prefix + "plain.graphml", True)
    assert not plain.is_fa()
    assert not plain.has_input_alphabet()
    assert not plain.has_output_alphabet()
except Exception:
    traceback.print_exc()
    exit(1)
exit(0)
