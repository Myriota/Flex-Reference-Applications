apps += [
  {
    'id': '001',
    'name': 'tracker',
    'c_files': files('main.c'),
    'variants': [
      {
        'name': '4_messages',
        'c_args': [
          '-DMESSAGES_PER_DAY=4'
        ],
      },
      {
        'name': '8_messages',
        'c_args': [
          '-DMESSAGES_PER_DAY=8'
        ],
      },
    ],
  },
]
