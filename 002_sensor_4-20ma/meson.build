apps += [
  {
    'id': '002',
    'name': 'sensor_4-20ma',
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
