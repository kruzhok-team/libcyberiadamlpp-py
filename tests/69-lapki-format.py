#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
#
#  The Lapki format test: the Lapki IDE dialect written for lapki-client and lapki-compiler
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
    source = sys.argv[0] + "-input.graphml"
    output = sys.argv[0] + "-lapki.graphml"

    # a document opened in the Lapki format is saved in it
    d = CyberiadaML.LocalDocument()
    d.open(source, CyberiadaML.formatLapki)
    assert d.get_file_format() == CyberiadaML.formatLapki
    assert d.get_file_format_str() == "Cyberiada-GraphML-Lapki"
    d.save_as(output, CyberiadaML.formatDetect)
    with open(output, encoding="utf-8") as f:
        written = f.read()
    assert '<data key="gFormat">Cyberiada-GraphML-1.0</data>' in written
    assert '<data key="dName">CGML_COMPONENT</data>' in written
    assert "id/ LED1" in written

    # the detected document is Cyberiada; the Lapki format is chosen on saving
    detected = CyberiadaML.LocalDocument()
    detected.open(output)
    assert detected.get_file_format() == CyberiadaML.formatCyberiada10
    detected.save_as(output, CyberiadaML.formatLapki)
    assert detected.get_file_format() == CyberiadaML.formatLapki
    print(detected.get_file_format_str())
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
