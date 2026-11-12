#!/usr/bin/python3
# -----------------------------------------------------------------------------
#  The Python binding for Cyberiada GraphML library
#
#  The test of the exception hierarchy: the classes mirror the C++ library
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

import os
import sys
import tempfile
import CyberiadaML

# the parent of each class, as in cyberiadamlpp.h; None is the builtin Exception
PARENTS = {
    'Exception': None,
    'FileException': 'Exception',
    'FormatException': 'Exception',
    'XMLException': 'FormatException',
    'CybMLException': 'FormatException',
    'ActionException': 'CybMLException',
    'MetainfoException': 'FormatException',
    'FAException': 'FormatException',
    'ParametersException': 'Exception',
    'NotFoundException': 'ParametersException',
    'AssertException': 'Exception',
    'NotImplementedException': 'Exception',
}

failures = []
for name, parent in PARENTS.items():
    base = Exception if parent is None else getattr(CyberiadaML, parent)
    if getattr(CyberiadaML, name).__bases__ != (base,):
        failures.append('{} derives from {}'.format(name, getattr(CyberiadaML, name).__bases__))

with tempfile.TemporaryDirectory() as tmp:
    broken = os.path.join(tmp, 'broken.graphml')
    with open(broken, 'w') as f:
        f.write('not a diagram\n')
    for family in (CyberiadaML.FormatException, CyberiadaML.Exception):
        try:
            CyberiadaML.LocalDocument().open(broken)
            failures.append('a file that is not XML is opened')
        except family as e:
            if type(e) is not CyberiadaML.XMLException:
                failures.append('a file that is not XML raises {}'.format(type(e).__name__))
        except Exception as e:
            failures.append('{} is not caught as {}'.format(type(e).__name__, family.__name__))
    try:
        CyberiadaML.LocalDocument(CyberiadaML.Document(), os.path.join(tmp, 'empty.graphml')).save()
        failures.append('an empty document is saved')
    except CyberiadaML.Exception as e:
        if type(e) is not CyberiadaML.ParametersException:
            failures.append('an empty document raises {}'.format(type(e).__name__))
    except Exception as e:
        failures.append('{} is not caught as Exception'.format(type(e).__name__))

for failure in failures:
    sys.stderr.write(failure + '\n')
exit(1 if failures else 0)
