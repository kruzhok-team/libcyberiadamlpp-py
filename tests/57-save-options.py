#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
# 
#  The document saving options test
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
    input_path = sys.argv[0] + "-input.graphml"
    out_path = sys.argv[0] + ".graphml"

    # the dialect is detected on reading
    doc = CyberiadaML.LocalDocument()
    doc.open(input_path)
    assert doc.get_file_format() == CyberiadaML.formatLegacyYED
    assert doc.get_file_format_str() == "yEd Berloga-1.6"

    assert CyberiadaML.is_legacy_yed_format(CyberiadaML.formatLegacyYED)
    assert CyberiadaML.is_legacy_yed_format(CyberiadaML.formatLegacyYEDOstranna)
    assert CyberiadaML.is_legacy_yed_format(CyberiadaML.formatLegacyYEDBerloga16)
    assert not CyberiadaML.is_legacy_yed_format(CyberiadaML.formatCyberiada10)

    # the yEd dialects are explicit write targets
    buffer = doc.encode(CyberiadaML.formatLegacyYEDOstranna)
    assert buffer.find("SchemeName") == -1
    buffer = doc.encode(CyberiadaML.formatLegacyYEDBerloga16)
    assert buffer.find("SchemeName") != -1
    assert buffer.find("coreMeta") != -1

    # the geometry cannot be skipped in the yEd format
    refused = False
    try:
        doc.encode(CyberiadaML.formatLegacyYEDOstranna, False, True)
    except CyberiadaML.ParametersException:
        refused = True
    assert refused

    # the checks are passed to the library
    buffer = doc.encode(CyberiadaML.formatCyberiada10, True, False, True, True, True)
    assert buffer

    # the document keeps its own file when the new one is refused
    refused = False
    try:
        doc.save_as(out_path, CyberiadaML.formatLegacyYEDOstranna, False, True)
    except CyberiadaML.ParametersException:
        refused = True
    assert refused
    assert doc.get_file_path() == input_path
    assert doc.get_file_format_str() == "yEd Berloga-1.6"

    # the saved document keeps the chosen dialect
    doc.save_as(out_path, CyberiadaML.formatLegacyYEDBerloga16)
    assert doc.get_file_format() == CyberiadaML.formatLegacyYEDBerloga16
    assert doc.get_file_format_str() == "yEd Berloga-1.6"

    reopened = CyberiadaML.LocalDocument()
    reopened.open(out_path)
    assert reopened.get_file_format_str() == "yEd Berloga-1.6"
    print("the saved document keeps the dialect")
except Exception as e:
    sys.stderr.write('Unexpected exception: {}\n'.format(e.__class__))
    sys.stderr.write('{}\n'.format(traceback.format_exc()))
    exit(1)

exit(0)
