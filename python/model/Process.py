class Process:

  def __init__(self, name, duration, priority, arrival_time):
    self.name = name
    self.duration = duration
    self.priority = priority
    self.arrival_time = arrival_time
    self.completion_time = 0
    self.turn_around_time = 0
    self.waiting_time = 0

  def __str__(self):
    return f'{self.name} - {self.duration} - {self.priority} - {self.completion_time} - {self.arrival_time}'


  def set_waiting_time(self, waiting_time):
    self.waiting_time = waiting_time

  def get_waiting_time(self):
    return self.waiting_time