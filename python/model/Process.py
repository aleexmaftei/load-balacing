class Process:

  def __init__(self, name, duration, priority, arrival_time):
    self.name = name
    self.duration = duration
    self.priority = priority
    self.arrival_time = arrival_time
    self.completion_time = 0

  def __str__(self):
    return f'{self.name} - {self.duration} - {self.priority} - {self.completion_time} - {self.arrival_time}'