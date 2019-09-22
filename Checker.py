import re

class Checker(object):
    def __init__(self, number=''):
        self.number = number

    def check(self):
        if re.match(r'^\d{3}-\d{4}$', self.number):
            print(self.number, ' is a valid US local phone number')
        else:
            print(self.number, ' rejected')
            raise ValueError('rejected')


Checker('555-1234').check()