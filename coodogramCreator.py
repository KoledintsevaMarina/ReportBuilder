import random

def target():
    coodogramType = "1"
    time = "%02d:%02d:%04d %02d.%02d.%02d" % (random.randint(1, 31),random.randint(1, 12),2016,random.randint(0, 24),random.randint(0, 60),random.randint(0, 60))
    pos  = "%04d,%04d,%04d" % (random.randint(0, 9999), random.randint(0, 9999), random.randint(0, 9999))
    speed= "%02d" % ( random.randint(1, 1000) )
    type = str( random.randint(0, 2) )
    fields = []    
    fields.append(coodogramType)
    fields.append(time)
    fields.append(pos)
    fields.append(speed)
    fields.append(type)
    return ",".join(fields)

def angle():
    coodogramType = "2"
    time = "%02d:%02d:%04d %02d.%02d.%02d" % (random.randint(1, 31),random.randint(1, 12),2016,random.randint(0, 24),random.randint(0, 60),random.randint(0, 60))
    angleZX= "%02d" % ( random.randint(0, 360) )
    angleZY= "%02d" % ( random.randint(0, 90) )
    fields = []    
    fields.append(coodogramType)
    fields.append(time)
    fields.append(angleZX)
    fields.append(angleZY)
    return ",".join(fields)
    
def power():
    coodogramType = "3"
    time = "%02d:%02d:%04d %02d.%02d.%02d" % (random.randint(1, 31),random.randint(1, 12),2016,random.randint(0, 24),random.randint(0, 60),random.randint(0, 60))
    power = "%02d" % ( random.randint(1, 1000) )
    fields = []
    fields.append(coodogramType)
    fields.append(time)
    fields.append(power)
    return ",".join(fields)
    
def mode():
    coodogramType = "4"
    time = "%02d:%02d:%04d %02d.%02d.%02d" % (random.randint(1, 31),random.randint(1, 12),2016,random.randint(0, 24),random.randint(0, 60),random.randint(0, 60))
    mode  = "%01d" % ( random.randint(0, 1) )
    fields = []
    fields.append(coodogramType)
    fields.append(time)
    fields.append(mode)
    return ",".join(fields)

coodogramGenerates = []
coodogramGenerates.append(target)
coodogramGenerates.append(angle)
coodogramGenerates.append(power)
coodogramGenerates.append(mode)

for i in range(0, 25):
    generator = coodogramGenerates[ random.randint(0, len(coodogramGenerates)-1) ]
    print(generator())