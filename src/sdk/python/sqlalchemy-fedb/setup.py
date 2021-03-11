#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright 2021 4Paradigm
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#   http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

from setuptools import setup, find_packages

setup(
    name='sqlalchemy-fedb',
    version='1.3.0',
    author='fedb Team',
    author_email=' g_featureengine@4paradigm.com',
    url='https://www.4paradigm.com',
    description='feDB adapter for SQLAlchemy',
    license="copyright 4paradigm.com",
    classifiers=[
        'Programming Language :: Python :: 3',
        ],
    install_requires=[
        "sqlalchemy"
    ],
    include_package_data=True,
    package_data = {'':['*.so']},
    packages=find_packages(),
    entry_points={
        'sqlalchemy.dialects': [
            'fedb = sqlalchemy_fedb.safedb:FeDBDialect',
        ],
    },
)
